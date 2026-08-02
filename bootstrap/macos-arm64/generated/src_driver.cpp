#include "src_driver.hpp"
#include <cmath>
#include "src_compiler.hpp"
#include "src_diagnostics.hpp"
#include "src_cli.hpp"
#include "src_external_dependency.hpp"
#include "src_dependency_policy.hpp"
#include "src_emitter_project.hpp"
#include "src_emitter_names.hpp"
#include "src_emitter_module.hpp"
#include "src_frontend_cache.hpp"
#include "src_module_acquisition.hpp"
#include "src_native_build_driver.hpp"
#include "src_package_manifest.hpp"
#include "src_package_acquisition.hpp"
#include "src_macos_app.hpp"
#include "src_macos_app_driver.hpp"
#include "src_ios_app.hpp"
#include "src_ios_app_driver.hpp"
#include "src_ios_device.hpp"
#include "src_parser.hpp"
#include "src_project.hpp"
#include "src_provenance.hpp"
#include "src_resolver.hpp"
#include "src_run_command.hpp"
#include "src_semantic.hpp"
#include "src_std_catalog.hpp"
#include "src_test_runner.hpp"
#include "std_blob_index.hpp"
#include "std_crypto_index.hpp"
#include "std_fs_index.hpp"
#include "std_os_index.hpp"
#include "std_path_index.hpp"
#include "std_http_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_analyzer_ { void __doof_initialize_module(); }
namespace app_src_emitter_names_ { void __doof_initialize_module(); }
namespace std_::time::duration { void __doof_initialize_module(); }
namespace std_::time::temporal { void __doof_initialize_module(); }
namespace app_src_external_dependency_ { void __doof_initialize_module(); }
namespace app_src_package_acquisition_ { void __doof_initialize_module(); }
namespace app_src_driver_ { void __doof_initialize_module(); }

namespace app_src_driver_ {
using namespace ::app_src_compiler_;
using namespace ::app_src_diagnostics_;
using namespace ::app_src_cli_;
using namespace ::app_src_external_dependency_;
using namespace ::app_src_dependency_policy_;
using namespace ::app_src_emitter_project_;
using namespace ::app_src_emitter_names_;
using namespace ::app_src_emitter_module_;
using namespace ::app_src_frontend_cache_;
using namespace ::app_src_module_acquisition_;
using namespace ::app_src_native_build_driver_;
using namespace ::app_src_package_manifest_;
using namespace ::app_src_package_acquisition_;
using namespace ::app_src_macos_app_;
using namespace ::app_src_macos_app_driver_;
using namespace ::app_src_ios_app_;
using namespace ::app_src_ios_app_driver_;
using namespace ::app_src_ios_device_;
using namespace ::app_src_parser_;
using namespace ::app_src_project_;
using namespace ::app_src_provenance_;
using namespace ::app_src_resolver_;
using namespace ::app_src_run_command_;
using namespace ::app_src_semantic_;
using namespace ::app_src_std_catalog_;
using namespace ::app_src_test_runner_;
using namespace ::std_::blob::index;
using namespace ::std_::crypto::index;
using namespace ::std_::fs::index;
using namespace ::std_::os::index;
using namespace ::std_::path::index;
int32_t MAX_PRINTED_DIAGNOSTICS = 8;
int64_t MAX_NATIVE_COMPILER_OUTPUT_BYTES = 262144LL;
int64_t MAX_COVERAGE_OUTPUT_BYTES = 16777216LL;
std::string hostPlatform() {
    const auto value = ::std_::os::index::platform();
    return ((value == std::string("darwin")) ? std::string("macos") : value);
}

doof::JsonObject NativeCommandResult::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["exitCode"] = doof::json_value(this->exitCode);
    (*_json)["output"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->output->size()); for (const auto& _element : *this->output) { _array->push_back(doof::json_value(static_cast<int32_t>(_element))); } return doof::json_value(_array); }();
    (*_json)["error"] = doof::json_value(this->error);
    (*_json)["truncated"] = doof::json_value(this->truncated);
    return _json;
}
doof::Result<std::shared_ptr<NativeCommandResult>, std::string> NativeCommandResult::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_exitCode = _object->find("exitCode");
    if (_iterator_exitCode == _object->end()) { return doof::Failure<std::string>{"Missing required field \"exitCode\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_exitCode->second) : doof::json_is_number(_iterator_exitCode->second)))) { return doof::Failure<std::string>{"Field \"exitCode\" expected number but got " + std::string(doof::json_type_name(_iterator_exitCode->second))}; }
    auto _field_exitCode = (_lenient ? doof::json_as_int_lenient(_iterator_exitCode->second) : doof::json_as_int(_iterator_exitCode->second));
    std::optional<std::shared_ptr<std::vector<uint8_t>>> _field_output;
    if (auto _iterator_output = _object->find("output"); _iterator_output != _object->end()) {
        if (!(doof::json_is_array(_iterator_output->second))) { return doof::Failure<std::string>{"Field \"output\" expected array but got " + std::string(doof::json_type_name(_iterator_output->second))}; }
        _field_output = [&]() { const auto* _array = doof::json_as_array(_iterator_output->second); auto _values = std::make_shared<std::vector<uint8_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(static_cast<uint8_t>(_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    } else {
        _field_output = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    }
    std::optional<std::string> _field_error;
    if (auto _iterator_error = _object->find("error"); _iterator_error != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_error->second) : doof::json_is_string(_iterator_error->second)))) { return doof::Failure<std::string>{"Field \"error\" expected string but got " + std::string(doof::json_type_name(_iterator_error->second))}; }
        _field_error = (_lenient ? doof::json_as_string_lenient(_iterator_error->second) : doof::json_as_string(_iterator_error->second));
    } else {
        _field_error = std::string("");
    }
    auto _iterator_truncated = _object->find("truncated");
    if (_iterator_truncated == _object->end()) { return doof::Failure<std::string>{"Missing required field \"truncated\""}; }
    if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_truncated->second) : doof::json_is_boolean(_iterator_truncated->second)))) { return doof::Failure<std::string>{"Field \"truncated\" expected boolean but got " + std::string(doof::json_type_name(_iterator_truncated->second))}; }
    auto _field_truncated = (_lenient ? doof::json_as_bool_lenient(_iterator_truncated->second) : doof::json_as_bool(_iterator_truncated->second));
    return doof::Success<std::shared_ptr<NativeCommandResult>>{std::make_shared<NativeCommandResult>(_field_exitCode, _field_output.value(), _field_error.value(), _field_truncated)};
}
std::shared_ptr<NativeCommandResult> runNativeCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::optional<std::string>& directory, bool inheritOutput, int64_t maxOutputBytes) {
    auto _binding_value_1 = ::std_::os::index::run(command, arguments, std::make_shared<::std_::os::index::ExecOptions>(directory, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, inheritOutput, maxOutputBytes, nullptr));
    if (doof::is_failure(_binding_value_1)) {
        const auto error = doof::failure_error(_binding_value_1);
        return std::make_shared<NativeCommandResult>(-1, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), error, false);
    }
    const auto executed = doof::success_value(_binding_value_1);
    std::shared_ptr<std::vector<uint8_t>> output = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    if (!inheritOutput) {
        (output = executed->stdout);
    }
    return std::make_shared<NativeCommandResult>(executed->exitCode, output, std::string(""), executed->stdoutTruncated);
}
int32_t printNativeCommandOutput(const std::shared_ptr<NativeCommandResult>& result, int32_t remainingLines) {
    auto remaining = remainingLines;
    const auto output = ((result->error != std::string("")) ? result->error : ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size()))));
    const auto& _iterable_2 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_2) {
        if (line == std::string("")) {
            continue;
        }
        if (remaining <= 0) {
            return 0;
        }
        doof::println(line);
        (remaining -= 1);
    }
    return remaining;
}
std::string driverWithExtension(const std::string& path) {
    if (doof::string_endsWith(path, std::string(".do"))) {
        return path;
    }
    return (path + std::string(".do"));
}
std::string driverLogicalPath(const std::string& path) {
    const auto withExtension = driverWithExtension(path);
    if (doof::string_startsWith(withExtension, std::string("/"))) {
        return driverSourceSuffix(withExtension);
    }
    return (std::string("/") + withExtension);
}
std::string driverSourceSuffix(const std::string& path) {
    const auto marker = std::string("/src/");
    auto index = 0;
    while ((index + static_cast<int32_t>(marker.size())) <= static_cast<int32_t>(path.size())) {
        if (doof::string_substring(path, index, (index + static_cast<int32_t>(marker.size()))) == marker) {
            return doof::string_substring(path, index, static_cast<int32_t>(path.size()));
        }
        (index = (index + 1));
    }
    return path;
}
std::string driverOutputPath(const std::string& directory, const std::string& name) {
    if (doof::string_endsWith(directory, std::string("/"))) {
        return (directory + name);
    }
    return ((directory + std::string("/")) + name);
}

doof::JsonObject DriverSourceRoot::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["logicalPrefix"] = doof::json_value(this->logicalPrefix);
    (*_json)["diskRoot"] = doof::json_value(this->diskRoot);
    return _json;
}
doof::Result<std::shared_ptr<DriverSourceRoot>, std::string> DriverSourceRoot::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_logicalPrefix = _object->find("logicalPrefix");
    if (_iterator_logicalPrefix == _object->end()) { return doof::Failure<std::string>{"Missing required field \"logicalPrefix\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_logicalPrefix->second) : doof::json_is_string(_iterator_logicalPrefix->second)))) { return doof::Failure<std::string>{"Field \"logicalPrefix\" expected string but got " + std::string(doof::json_type_name(_iterator_logicalPrefix->second))}; }
    auto _field_logicalPrefix = (_lenient ? doof::json_as_string_lenient(_iterator_logicalPrefix->second) : doof::json_as_string(_iterator_logicalPrefix->second));
    auto _iterator_diskRoot = _object->find("diskRoot");
    if (_iterator_diskRoot == _object->end()) { return doof::Failure<std::string>{"Missing required field \"diskRoot\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_diskRoot->second) : doof::json_is_string(_iterator_diskRoot->second)))) { return doof::Failure<std::string>{"Field \"diskRoot\" expected string but got " + std::string(doof::json_type_name(_iterator_diskRoot->second))}; }
    auto _field_diskRoot = (_lenient ? doof::json_as_string_lenient(_iterator_diskRoot->second) : doof::json_as_string(_iterator_diskRoot->second));
    return doof::Success<std::shared_ptr<DriverSourceRoot>>{std::make_shared<DriverSourceRoot>(_field_logicalPrefix, _field_diskRoot)};
}

doof::JsonObject DriverReachedPackage::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["acquisition"] = doof::json_value(this->acquisition->toJsonObject());
    (*_json)["manifest"] = doof::json_value(this->manifest->toJsonObject());
    (*_json)["introducedBy"] = doof::json_value(this->introducedBy);
    (*_json)["sourceKind"] = doof::json_value(this->sourceKind);
    (*_json)["sourceUrl"] = doof::json_value(this->sourceUrl);
    (*_json)["sourceRef"] = doof::json_value(this->sourceRef);
    (*_json)["sourceCommit"] = doof::json_value(this->sourceCommit);
    (*_json)["requestedUrl"] = doof::json_value(this->requestedUrl);
    (*_json)["requestedRef"] = doof::json_value(this->requestedRef);
    (*_json)["requestedCommit"] = doof::json_value(this->requestedCommit);
    (*_json)["mutable"] = doof::json_value(this->mutable_);
    return _json;
}
doof::Result<std::shared_ptr<DriverReachedPackage>, std::string> DriverReachedPackage::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_acquisition = _object->find("acquisition");
    if (_iterator_acquisition == _object->end()) { return doof::Failure<std::string>{"Missing required field \"acquisition\""}; }
    if (!(doof::json_is_object(_iterator_acquisition->second))) { return doof::Failure<std::string>{"Field \"acquisition\" expected object but got " + std::string(doof::json_type_name(_iterator_acquisition->second))}; }
    auto _field_acquisition = doof::success_value(::app_src_module_acquisition_::ModuleAcquisition::fromJsonValue(_iterator_acquisition->second, _lenient));
    auto _iterator_manifest = _object->find("manifest");
    if (_iterator_manifest == _object->end()) { return doof::Failure<std::string>{"Missing required field \"manifest\""}; }
    if (!(doof::json_is_object(_iterator_manifest->second))) { return doof::Failure<std::string>{"Field \"manifest\" expected object but got " + std::string(doof::json_type_name(_iterator_manifest->second))}; }
    auto _field_manifest = doof::success_value(::app_src_package_manifest_::PackageManifest::fromJsonValue(_iterator_manifest->second, _lenient));
    auto _iterator_introducedBy = _object->find("introducedBy");
    if (_iterator_introducedBy == _object->end()) { return doof::Failure<std::string>{"Missing required field \"introducedBy\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_introducedBy->second) : doof::json_is_string(_iterator_introducedBy->second)))) { return doof::Failure<std::string>{"Field \"introducedBy\" expected string but got " + std::string(doof::json_type_name(_iterator_introducedBy->second))}; }
    auto _field_introducedBy = (_lenient ? doof::json_as_string_lenient(_iterator_introducedBy->second) : doof::json_as_string(_iterator_introducedBy->second));
    auto _iterator_sourceKind = _object->find("sourceKind");
    if (_iterator_sourceKind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourceKind\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceKind->second) : doof::json_is_string(_iterator_sourceKind->second)))) { return doof::Failure<std::string>{"Field \"sourceKind\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceKind->second))}; }
    auto _field_sourceKind = (_lenient ? doof::json_as_string_lenient(_iterator_sourceKind->second) : doof::json_as_string(_iterator_sourceKind->second));
    std::optional<std::string> _field_sourceUrl;
    if (auto _iterator_sourceUrl = _object->find("sourceUrl"); _iterator_sourceUrl != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceUrl->second) : doof::json_is_string(_iterator_sourceUrl->second)))) { return doof::Failure<std::string>{"Field \"sourceUrl\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceUrl->second))}; }
        _field_sourceUrl = (_lenient ? doof::json_as_string_lenient(_iterator_sourceUrl->second) : doof::json_as_string(_iterator_sourceUrl->second));
    } else {
        _field_sourceUrl = std::string("");
    }
    std::optional<std::string> _field_sourceRef;
    if (auto _iterator_sourceRef = _object->find("sourceRef"); _iterator_sourceRef != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceRef->second) : doof::json_is_string(_iterator_sourceRef->second)))) { return doof::Failure<std::string>{"Field \"sourceRef\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceRef->second))}; }
        _field_sourceRef = (_lenient ? doof::json_as_string_lenient(_iterator_sourceRef->second) : doof::json_as_string(_iterator_sourceRef->second));
    } else {
        _field_sourceRef = std::string("");
    }
    std::optional<std::string> _field_sourceCommit;
    if (auto _iterator_sourceCommit = _object->find("sourceCommit"); _iterator_sourceCommit != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceCommit->second) : doof::json_is_string(_iterator_sourceCommit->second)))) { return doof::Failure<std::string>{"Field \"sourceCommit\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceCommit->second))}; }
        _field_sourceCommit = (_lenient ? doof::json_as_string_lenient(_iterator_sourceCommit->second) : doof::json_as_string(_iterator_sourceCommit->second));
    } else {
        _field_sourceCommit = std::string("");
    }
    std::optional<std::string> _field_requestedUrl;
    if (auto _iterator_requestedUrl = _object->find("requestedUrl"); _iterator_requestedUrl != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_requestedUrl->second) : doof::json_is_string(_iterator_requestedUrl->second)))) { return doof::Failure<std::string>{"Field \"requestedUrl\" expected string but got " + std::string(doof::json_type_name(_iterator_requestedUrl->second))}; }
        _field_requestedUrl = (_lenient ? doof::json_as_string_lenient(_iterator_requestedUrl->second) : doof::json_as_string(_iterator_requestedUrl->second));
    } else {
        _field_requestedUrl = std::string("");
    }
    std::optional<std::string> _field_requestedRef;
    if (auto _iterator_requestedRef = _object->find("requestedRef"); _iterator_requestedRef != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_requestedRef->second) : doof::json_is_string(_iterator_requestedRef->second)))) { return doof::Failure<std::string>{"Field \"requestedRef\" expected string but got " + std::string(doof::json_type_name(_iterator_requestedRef->second))}; }
        _field_requestedRef = (_lenient ? doof::json_as_string_lenient(_iterator_requestedRef->second) : doof::json_as_string(_iterator_requestedRef->second));
    } else {
        _field_requestedRef = std::string("");
    }
    std::optional<std::string> _field_requestedCommit;
    if (auto _iterator_requestedCommit = _object->find("requestedCommit"); _iterator_requestedCommit != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_requestedCommit->second) : doof::json_is_string(_iterator_requestedCommit->second)))) { return doof::Failure<std::string>{"Field \"requestedCommit\" expected string but got " + std::string(doof::json_type_name(_iterator_requestedCommit->second))}; }
        _field_requestedCommit = (_lenient ? doof::json_as_string_lenient(_iterator_requestedCommit->second) : doof::json_as_string(_iterator_requestedCommit->second));
    } else {
        _field_requestedCommit = std::string("");
    }
    std::optional<bool> _field_mutable_;
    if (auto _iterator_mutable_ = _object->find("mutable"); _iterator_mutable_ != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_mutable_->second) : doof::json_is_boolean(_iterator_mutable_->second)))) { return doof::Failure<std::string>{"Field \"mutable\" expected boolean but got " + std::string(doof::json_type_name(_iterator_mutable_->second))}; }
        _field_mutable_ = (_lenient ? doof::json_as_bool_lenient(_iterator_mutable_->second) : doof::json_as_bool(_iterator_mutable_->second));
    } else {
        _field_mutable_ = false;
    }
    return doof::Success<std::shared_ptr<DriverReachedPackage>>{std::make_shared<DriverReachedPackage>(_field_acquisition, _field_manifest, _field_introducedBy, _field_sourceKind, _field_sourceUrl.value(), _field_sourceRef.value(), _field_sourceCommit.value(), _field_requestedUrl.value(), _field_requestedRef.value(), _field_requestedCommit.value(), _field_mutable_.value())};
}

doof::JsonObject DriverAcquiredSource::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["acquisition"] = doof::json_value(this->acquisition->toJsonObject());
    (*_json)["introducedBy"] = doof::json_value(this->introducedBy);
    (*_json)["sourceKind"] = doof::json_value(this->sourceKind);
    (*_json)["sourceUrl"] = doof::json_value(this->sourceUrl);
    (*_json)["sourceRef"] = doof::json_value(this->sourceRef);
    (*_json)["sourceCommit"] = doof::json_value(this->sourceCommit);
    (*_json)["requestedUrl"] = doof::json_value(this->requestedUrl);
    (*_json)["requestedRef"] = doof::json_value(this->requestedRef);
    (*_json)["requestedCommit"] = doof::json_value(this->requestedCommit);
    (*_json)["mutable"] = doof::json_value(this->mutable_);
    return _json;
}
doof::Result<std::shared_ptr<DriverAcquiredSource>, std::string> DriverAcquiredSource::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_acquisition = _object->find("acquisition");
    if (_iterator_acquisition == _object->end()) { return doof::Failure<std::string>{"Missing required field \"acquisition\""}; }
    if (!(doof::json_is_object(_iterator_acquisition->second))) { return doof::Failure<std::string>{"Field \"acquisition\" expected object but got " + std::string(doof::json_type_name(_iterator_acquisition->second))}; }
    auto _field_acquisition = doof::success_value(::app_src_module_acquisition_::ModuleAcquisition::fromJsonValue(_iterator_acquisition->second, _lenient));
    auto _iterator_introducedBy = _object->find("introducedBy");
    if (_iterator_introducedBy == _object->end()) { return doof::Failure<std::string>{"Missing required field \"introducedBy\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_introducedBy->second) : doof::json_is_string(_iterator_introducedBy->second)))) { return doof::Failure<std::string>{"Field \"introducedBy\" expected string but got " + std::string(doof::json_type_name(_iterator_introducedBy->second))}; }
    auto _field_introducedBy = (_lenient ? doof::json_as_string_lenient(_iterator_introducedBy->second) : doof::json_as_string(_iterator_introducedBy->second));
    auto _iterator_sourceKind = _object->find("sourceKind");
    if (_iterator_sourceKind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourceKind\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceKind->second) : doof::json_is_string(_iterator_sourceKind->second)))) { return doof::Failure<std::string>{"Field \"sourceKind\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceKind->second))}; }
    auto _field_sourceKind = (_lenient ? doof::json_as_string_lenient(_iterator_sourceKind->second) : doof::json_as_string(_iterator_sourceKind->second));
    std::optional<std::string> _field_sourceUrl;
    if (auto _iterator_sourceUrl = _object->find("sourceUrl"); _iterator_sourceUrl != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceUrl->second) : doof::json_is_string(_iterator_sourceUrl->second)))) { return doof::Failure<std::string>{"Field \"sourceUrl\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceUrl->second))}; }
        _field_sourceUrl = (_lenient ? doof::json_as_string_lenient(_iterator_sourceUrl->second) : doof::json_as_string(_iterator_sourceUrl->second));
    } else {
        _field_sourceUrl = std::string("");
    }
    std::optional<std::string> _field_sourceRef;
    if (auto _iterator_sourceRef = _object->find("sourceRef"); _iterator_sourceRef != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceRef->second) : doof::json_is_string(_iterator_sourceRef->second)))) { return doof::Failure<std::string>{"Field \"sourceRef\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceRef->second))}; }
        _field_sourceRef = (_lenient ? doof::json_as_string_lenient(_iterator_sourceRef->second) : doof::json_as_string(_iterator_sourceRef->second));
    } else {
        _field_sourceRef = std::string("");
    }
    std::optional<std::string> _field_sourceCommit;
    if (auto _iterator_sourceCommit = _object->find("sourceCommit"); _iterator_sourceCommit != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceCommit->second) : doof::json_is_string(_iterator_sourceCommit->second)))) { return doof::Failure<std::string>{"Field \"sourceCommit\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceCommit->second))}; }
        _field_sourceCommit = (_lenient ? doof::json_as_string_lenient(_iterator_sourceCommit->second) : doof::json_as_string(_iterator_sourceCommit->second));
    } else {
        _field_sourceCommit = std::string("");
    }
    std::optional<std::string> _field_requestedUrl;
    if (auto _iterator_requestedUrl = _object->find("requestedUrl"); _iterator_requestedUrl != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_requestedUrl->second) : doof::json_is_string(_iterator_requestedUrl->second)))) { return doof::Failure<std::string>{"Field \"requestedUrl\" expected string but got " + std::string(doof::json_type_name(_iterator_requestedUrl->second))}; }
        _field_requestedUrl = (_lenient ? doof::json_as_string_lenient(_iterator_requestedUrl->second) : doof::json_as_string(_iterator_requestedUrl->second));
    } else {
        _field_requestedUrl = std::string("");
    }
    std::optional<std::string> _field_requestedRef;
    if (auto _iterator_requestedRef = _object->find("requestedRef"); _iterator_requestedRef != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_requestedRef->second) : doof::json_is_string(_iterator_requestedRef->second)))) { return doof::Failure<std::string>{"Field \"requestedRef\" expected string but got " + std::string(doof::json_type_name(_iterator_requestedRef->second))}; }
        _field_requestedRef = (_lenient ? doof::json_as_string_lenient(_iterator_requestedRef->second) : doof::json_as_string(_iterator_requestedRef->second));
    } else {
        _field_requestedRef = std::string("");
    }
    std::optional<std::string> _field_requestedCommit;
    if (auto _iterator_requestedCommit = _object->find("requestedCommit"); _iterator_requestedCommit != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_requestedCommit->second) : doof::json_is_string(_iterator_requestedCommit->second)))) { return doof::Failure<std::string>{"Field \"requestedCommit\" expected string but got " + std::string(doof::json_type_name(_iterator_requestedCommit->second))}; }
        _field_requestedCommit = (_lenient ? doof::json_as_string_lenient(_iterator_requestedCommit->second) : doof::json_as_string(_iterator_requestedCommit->second));
    } else {
        _field_requestedCommit = std::string("");
    }
    std::optional<bool> _field_mutable_;
    if (auto _iterator_mutable_ = _object->find("mutable"); _iterator_mutable_ != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_mutable_->second) : doof::json_is_boolean(_iterator_mutable_->second)))) { return doof::Failure<std::string>{"Field \"mutable\" expected boolean but got " + std::string(doof::json_type_name(_iterator_mutable_->second))}; }
        _field_mutable_ = (_lenient ? doof::json_as_bool_lenient(_iterator_mutable_->second) : doof::json_as_bool(_iterator_mutable_->second));
    } else {
        _field_mutable_ = false;
    }
    return doof::Success<std::shared_ptr<DriverAcquiredSource>>{std::make_shared<DriverAcquiredSource>(_field_acquisition, _field_introducedBy, _field_sourceKind, _field_sourceUrl.value(), _field_sourceRef.value(), _field_sourceCommit.value(), _field_requestedUrl.value(), _field_requestedRef.value(), _field_requestedCommit.value(), _field_mutable_.value())};
}

doof::JsonObject DriverSourceState::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["localRoots"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->localRoots->size()); for (const auto& _element : *this->localRoots) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["acquisitions"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->acquisitions->size()); for (const auto& _element : *this->acquisitions) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["acquiredSources"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->acquiredSources->size()); for (const auto& _element : *this->acquiredSources) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["reachedPackages"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->reachedPackages->size()); for (const auto& _element : *this->reachedPackages) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["namespaceMappings"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->namespaceMappings->size()); for (const auto& _element : *this->namespaceMappings) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["nativePlatform"] = doof::json_value(this->nativePlatform);
    (*_json)["externalTarget"] = doof::json_value(this->externalTarget->toJsonObject());
    (*_json)["rootManifest"] = doof::json_value(this->rootManifest->toJsonObject());
    (*_json)["stdCatalog"] = doof::json_value(this->stdCatalog->toJsonObject());
    (*_json)["packageAcquisitionRoot"] = doof::json_value(this->packageAcquisitionRoot);
    return _json;
}
doof::Result<std::shared_ptr<DriverSourceState>, std::string> DriverSourceState::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_localRoots = _object->find("localRoots");
    if (_iterator_localRoots == _object->end()) { return doof::Failure<std::string>{"Missing required field \"localRoots\""}; }
    if (!(doof::json_is_array(_iterator_localRoots->second))) { return doof::Failure<std::string>{"Field \"localRoots\" expected array but got " + std::string(doof::json_type_name(_iterator_localRoots->second))}; }
    auto _field_localRoots = [&]() { const auto* _array = doof::json_as_array(_iterator_localRoots->second); auto _values = std::make_shared<std::vector<std::shared_ptr<DriverSourceRoot>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(DriverSourceRoot::fromJsonValue(_element, _lenient))); } return _values; }();
    auto _iterator_acquisitions = _object->find("acquisitions");
    if (_iterator_acquisitions == _object->end()) { return doof::Failure<std::string>{"Missing required field \"acquisitions\""}; }
    if (!(doof::json_is_array(_iterator_acquisitions->second))) { return doof::Failure<std::string>{"Field \"acquisitions\" expected array but got " + std::string(doof::json_type_name(_iterator_acquisitions->second))}; }
    auto _field_acquisitions = [&]() { const auto* _array = doof::json_as_array(_iterator_acquisitions->second); auto _values = std::make_shared<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(::app_src_module_acquisition_::ModuleAcquisition::fromJsonValue(_element, _lenient))); } return _values; }();
    auto _iterator_acquiredSources = _object->find("acquiredSources");
    if (_iterator_acquiredSources == _object->end()) { return doof::Failure<std::string>{"Missing required field \"acquiredSources\""}; }
    if (!(doof::json_is_array(_iterator_acquiredSources->second))) { return doof::Failure<std::string>{"Field \"acquiredSources\" expected array but got " + std::string(doof::json_type_name(_iterator_acquiredSources->second))}; }
    auto _field_acquiredSources = [&]() { const auto* _array = doof::json_as_array(_iterator_acquiredSources->second); auto _values = std::make_shared<std::vector<std::shared_ptr<DriverAcquiredSource>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(DriverAcquiredSource::fromJsonValue(_element, _lenient))); } return _values; }();
    auto _iterator_reachedPackages = _object->find("reachedPackages");
    if (_iterator_reachedPackages == _object->end()) { return doof::Failure<std::string>{"Missing required field \"reachedPackages\""}; }
    if (!(doof::json_is_array(_iterator_reachedPackages->second))) { return doof::Failure<std::string>{"Field \"reachedPackages\" expected array but got " + std::string(doof::json_type_name(_iterator_reachedPackages->second))}; }
    auto _field_reachedPackages = [&]() { const auto* _array = doof::json_as_array(_iterator_reachedPackages->second); auto _values = std::make_shared<std::vector<std::shared_ptr<DriverReachedPackage>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(DriverReachedPackage::fromJsonValue(_element, _lenient))); } return _values; }();
    auto _iterator_namespaceMappings = _object->find("namespaceMappings");
    if (_iterator_namespaceMappings == _object->end()) { return doof::Failure<std::string>{"Missing required field \"namespaceMappings\""}; }
    if (!(doof::json_is_array(_iterator_namespaceMappings->second))) { return doof::Failure<std::string>{"Field \"namespaceMappings\" expected array but got " + std::string(doof::json_type_name(_iterator_namespaceMappings->second))}; }
    auto _field_namespaceMappings = [&]() { const auto* _array = doof::json_as_array(_iterator_namespaceMappings->second); auto _values = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(::app_src_emitter_names_::ModuleNamespaceMapping::fromJsonValue(_element, _lenient))); } return _values; }();
    auto _iterator_nativePlatform = _object->find("nativePlatform");
    if (_iterator_nativePlatform == _object->end()) { return doof::Failure<std::string>{"Missing required field \"nativePlatform\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_nativePlatform->second) : doof::json_is_string(_iterator_nativePlatform->second)))) { return doof::Failure<std::string>{"Field \"nativePlatform\" expected string but got " + std::string(doof::json_type_name(_iterator_nativePlatform->second))}; }
    auto _field_nativePlatform = (_lenient ? doof::json_as_string_lenient(_iterator_nativePlatform->second) : doof::json_as_string(_iterator_nativePlatform->second));
    auto _iterator_externalTarget = _object->find("externalTarget");
    if (_iterator_externalTarget == _object->end()) { return doof::Failure<std::string>{"Missing required field \"externalTarget\""}; }
    if (!(doof::json_is_object(_iterator_externalTarget->second))) { return doof::Failure<std::string>{"Field \"externalTarget\" expected object but got " + std::string(doof::json_type_name(_iterator_externalTarget->second))}; }
    auto _field_externalTarget = doof::success_value(::app_src_external_dependency_::ExternalDependencyTarget::fromJsonValue(_iterator_externalTarget->second, _lenient));
    auto _iterator_rootManifest = _object->find("rootManifest");
    if (_iterator_rootManifest == _object->end()) { return doof::Failure<std::string>{"Missing required field \"rootManifest\""}; }
    if (!(doof::json_is_object(_iterator_rootManifest->second))) { return doof::Failure<std::string>{"Field \"rootManifest\" expected object but got " + std::string(doof::json_type_name(_iterator_rootManifest->second))}; }
    auto _field_rootManifest = doof::success_value(::app_src_package_manifest_::PackageManifest::fromJsonValue(_iterator_rootManifest->second, _lenient));
    auto _iterator_stdCatalog = _object->find("stdCatalog");
    if (_iterator_stdCatalog == _object->end()) { return doof::Failure<std::string>{"Missing required field \"stdCatalog\""}; }
    if (!(doof::json_is_object(_iterator_stdCatalog->second))) { return doof::Failure<std::string>{"Field \"stdCatalog\" expected object but got " + std::string(doof::json_type_name(_iterator_stdCatalog->second))}; }
    auto _field_stdCatalog = doof::success_value(::app_src_std_catalog_::StdCatalog::fromJsonValue(_iterator_stdCatalog->second, _lenient));
    auto _iterator_packageAcquisitionRoot = _object->find("packageAcquisitionRoot");
    if (_iterator_packageAcquisitionRoot == _object->end()) { return doof::Failure<std::string>{"Missing required field \"packageAcquisitionRoot\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_packageAcquisitionRoot->second) : doof::json_is_string(_iterator_packageAcquisitionRoot->second)))) { return doof::Failure<std::string>{"Field \"packageAcquisitionRoot\" expected string but got " + std::string(doof::json_type_name(_iterator_packageAcquisitionRoot->second))}; }
    auto _field_packageAcquisitionRoot = (_lenient ? doof::json_as_string_lenient(_iterator_packageAcquisitionRoot->second) : doof::json_as_string(_iterator_packageAcquisitionRoot->second));
    return doof::Success<std::shared_ptr<DriverSourceState>>{std::make_shared<DriverSourceState>(_field_localRoots, _field_acquisitions, _field_acquiredSources, _field_reachedPackages, _field_namespaceMappings, _field_nativePlatform, _field_externalTarget, _field_rootManifest, _field_stdCatalog, _field_packageAcquisitionRoot)};
}
std::shared_ptr<DriverSourceState> configuredDriverSourceState;
std::string driverSourceDiskPath(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>>& localRoots, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>& acquisitions) {
    const auto& _iterable_3 = localRoots;
    for (const auto& root : *_iterable_3) {
        if (logicalPath == root->logicalPrefix) {
            return root->diskRoot;
        }
        const auto prefix = (root->logicalPrefix + std::string("/"));
        if (doof::string_startsWith(logicalPath, prefix)) {
            return ::app_src_project_::joinPath(root->diskRoot, doof::string_substring(logicalPath, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(logicalPath.size())));
        }
    }
    const auto acquiredPath = ::app_src_module_acquisition_::acquiredModuleDiskPath(logicalPath, acquisitions);
    if (!doof::is_null(acquiredPath)) {
        return acquiredPath.value();
    }
    return logicalPath;
}
doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> loadDriverSource(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>>& localRoots, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>& acquisitions) {
    const auto diskPath = driverSourceDiskPath(logicalPath, localRoots, acquisitions);
    if (!::doof_fs::exists(diskPath)) {
        return doof::Success<std::shared_ptr<::app_src_semantic_::SourceFile>>{ nullptr };
    }
    auto _binding_value_4 = ::doof_fs::readText(diskPath);
    if (doof::is_failure(_binding_value_4)) {
        const auto& source = _binding_value_4;
        return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{ driverDiagnostic(logicalPath, std::string("Could not read source file ") + doof::to_string(diskPath) + std::string("")) };
    }
    const auto source = doof::success_value(_binding_value_4);
    return doof::Success<std::shared_ptr<::app_src_semantic_::SourceFile>>{ std::make_shared<::app_src_semantic_::SourceFile>(logicalPath, source) };
}
doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> configuredDriverSource(const std::string& logicalPath) {
    if (doof::string_startsWith(logicalPath, std::string("/std/"))) {
        auto _binding_value_5 = ensureStdPackageAcquisition(logicalPath);
        if (doof::is_failure(_binding_value_5)) {
            const auto error = doof::failure_error(_binding_value_5);
            return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{ driverDiagnostic(logicalPath, error) };
        }
    }
    auto _try_value_6 = loadDriverSource(logicalPath, configuredDriverSourceState->localRoots, configuredDriverSourceState->acquisitions);
    if (doof::is_failure(_try_value_6)) return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{doof::failure_error(_try_value_6)};
    const auto source = doof::success_value(_try_value_6);
    if (!doof::is_null(source)) {
        const auto package = acquiredPackageForLoadedSource(logicalPath, configuredDriverSourceState);
        if (!doof::is_null(package)) {
            auto _try_value_7 = registerReachedPackage(doof::unwrap_optional(package));
            if (doof::is_failure(_try_value_7)) return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{doof::failure_error(_try_value_7)};
        }
    }
    return doof::Success<std::shared_ptr<::app_src_semantic_::SourceFile>>{ source };
}
std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquiredPackageForLoadedSource(const std::string& logicalPath, const std::shared_ptr<DriverSourceState>& state) {
    const auto& _iterable_8 = state->localRoots;
    for (const auto& root : *_iterable_8) {
        if ((logicalPath == root->logicalPrefix) || doof::string_startsWith(logicalPath, (root->logicalPrefix + std::string("/")))) {
            return nullptr;
        }
    }
    return ::app_src_module_acquisition_::acquiredPackageForModule(logicalPath, state->acquisitions);
}
doof::Result<void, std::shared_ptr<::app_src_semantic_::Diagnostic>> registerReachedPackage(const std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>& acquisition) {
    const auto& _iterable_9 = configuredDriverSourceState->reachedPackages;
    for (const auto& reached : *_iterable_9) {
        if ((reached->acquisition->logicalPrefix == acquisition->logicalPrefix) && (reached->acquisition->diskRoot == acquisition->diskRoot)) {
            return doof::Success<void>{};
        }
    }
    const auto manifestPath = ::app_src_module_acquisition_::acquiredManifestPath(acquisition);
    auto _binding_value_10 = ::doof_fs::readText(manifestPath);
    if (doof::is_failure(_binding_value_10)) {
        const auto& manifestSource = _binding_value_10;
        return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{ driverDiagnostic(manifestPath, std::string("Could not read doof.json for acquired package ") + doof::to_string(acquisition->logicalPrefix) + std::string(" at ") + doof::to_string(manifestPath) + std::string("")) };
    }
    const auto manifestSource = doof::success_value(_binding_value_10);
    auto _binding_value_11 = ::app_src_package_manifest_::parsePackageManifest(manifestSource, manifestPath, acquisition->diskRoot, configuredDriverSourceState->nativePlatform, std::string(""));
    if (doof::is_failure(_binding_value_11)) {
        const auto error = doof::failure_error(_binding_value_11);
        return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{ driverDiagnostic(manifestPath, error) };
    }
    const auto manifest = doof::success_value(_binding_value_11);
    if ((static_cast<int32_t>((manifest->packageResolutions)->size()) > 0) || (static_cast<int32_t>((manifest->externalResolutions)->size()) > 0)) {
        return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{ driverDiagnostic(manifestPath, std::string("resolutions are only allowed in the root doof.json")) };
    }
    const auto source = acquiredSourceFor(acquisition);
    configuredDriverSourceState->reachedPackages->push_back(std::make_shared<DriverReachedPackage>(acquisition, manifest, (doof::is_null(source) ? std::string("") : source->introducedBy), (doof::is_null(source) ? std::string("local") : source->sourceKind), (doof::is_null(source) ? std::string("") : source->sourceUrl), (doof::is_null(source) ? std::string("") : source->sourceRef), (doof::is_null(source) ? std::string("") : source->sourceCommit), (doof::is_null(source) ? std::string("") : source->requestedUrl), (doof::is_null(source) ? std::string("") : source->requestedRef), (doof::is_null(source) ? std::string("") : source->requestedCommit), (doof::is_null(source) ? true : source->mutable_)));
    configuredDriverSourceState->namespaceMappings->push_back(std::make_shared<::app_src_emitter_names_::ModuleNamespaceMapping>(acquisition->logicalPrefix, manifest->name, driverPackageOutputRoot(acquisition->logicalPrefix)));
    return doof::Success<void>{};
}
std::shared_ptr<DriverAcquiredSource> acquiredSourceFor(const std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>& acquisition) {
    const auto& _iterable_12 = configuredDriverSourceState->acquiredSources;
    for (const auto& source : *_iterable_12) {
        if ((source->acquisition->logicalPrefix == acquisition->logicalPrefix) && (source->acquisition->diskRoot == acquisition->diskRoot)) {
            return source;
        }
    }
    return nullptr;
}
doof::Result<void, std::string> ensureStdPackageAcquisition(const std::string& logicalPath) {
    if (!doof::is_null(::app_src_module_acquisition_::acquiredModuleDiskPath(logicalPath, configuredDriverSourceState->acquisitions))) {
        return doof::Success<void>{};
    }
    const auto remainder = doof::string_substring(logicalPath, 5, static_cast<int32_t>(logicalPath.size()));
    const auto slash = doof::string_indexOf(remainder, std::string("/"));
    const auto shortName = ((slash < 0) ? remainder : doof::string_substring(remainder, 0, slash));
    const auto packageName = (std::string("std/") + shortName);
    const auto package = ::app_src_std_catalog_::stdCatalogPackage(configuredDriverSourceState->stdCatalog, packageName);
    if (doof::is_null(package)) {
        return doof::Failure<std::string>{ (std::string("Unknown standard package ") + packageName) };
    }
    auto _binding_value_13 = ::app_src_package_acquisition_::acquireExactGitPackage(std::make_shared<::app_src_package_acquisition_::ExactPackageSource>(package->name, package->name, package->url, package->ref, package->commit), configuredDriverSourceState->packageAcquisitionRoot);
    if (doof::is_failure(_binding_value_13)) {
        const auto error = doof::failure_error(_binding_value_13);
        return doof::Failure<std::string>{ error };
    }
    const auto acquired = doof::success_value(_binding_value_13);
    const auto acquisition = std::make_shared<::app_src_module_acquisition_::ModuleAcquisition>((std::string("/") + packageName), acquired->rootDirectory);
    configuredDriverSourceState->acquisitions->push_back(acquisition);
    configuredDriverSourceState->acquiredSources->push_back(std::make_shared<DriverAcquiredSource>(acquisition, std::string(""), std::string("git"), package->url, package->ref, package->commit, std::string(""), std::string(""), std::string(""), false));
    return doof::Success<void>{};
}
doof::Result<void, std::string> ensureStdPackageReached(const std::string& packageName) {
    const auto logicalPath = ((std::string("/") + packageName) + std::string("/index.do"));
    auto _try_value_14 = ensureStdPackageAcquisition(logicalPath);
    if (doof::is_failure(_try_value_14)) return doof::Failure<std::string>{doof::failure_error(_try_value_14)};
    const auto acquisition = ::app_src_module_acquisition_::acquiredPackageForModule(logicalPath, configuredDriverSourceState->acquisitions);
    if (doof::is_null(acquisition)) {
        return doof::Failure<std::string>{ (std::string("Could not resolve required standard package ") + packageName) };
    }
    auto _binding_value_15 = registerReachedPackage(doof::unwrap_optional(acquisition));
    if (doof::is_failure(_binding_value_15)) {
        const auto error = doof::failure_error(_binding_value_15);
        return doof::Failure<std::string>{ error->message };
    }
    return doof::Success<void>{};
}
std::shared_ptr<::app_src_semantic_::Diagnostic> driverDiagnostic(const std::string& module, const std::string& message) {
    auto zero = ::app_src_semantic_::SemanticLocation{0, 0, 0};
    return std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), message, ::app_src_semantic_::SemanticSpan{zero, zero}, module, std::string(""));
}
std::string driverSourceDiskRoot(const std::string& path) {
    const auto marker = std::string("/src/");
    auto index = 0;
    while ((index + static_cast<int32_t>(marker.size())) <= static_cast<int32_t>(path.size())) {
        if (doof::string_substring(path, index, (index + static_cast<int32_t>(marker.size()))) == marker) {
            return doof::string_substring(path, 0, ((index + static_cast<int32_t>(marker.size())) - 1));
        }
        (index = (index + 1));
    }
    return std::string("");
}
doof::Result<doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>, std::string> sourceLoaderForRequest(const std::string& entryPath, const std::string& stdlibRoot, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>& namespaceMappings, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest, const std::string& nativePlatform, const std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>& externalTarget) {
    std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>> localRoots = std::make_shared<std::vector<std::shared_ptr<DriverSourceRoot>>>(std::vector<std::shared_ptr<DriverSourceRoot>>{});
    const auto rootLogicalPrefix = driverRootLogicalPrefix(rootManifest->name, rootManifest->rootDirectory);
    if (rootLogicalPrefix != driverLogicalPrefix(rootManifest->rootDirectory)) {
        localRoots->push_back(std::make_shared<DriverSourceRoot>(rootLogicalPrefix, rootManifest->rootDirectory));
    }
    const auto sourceRoot = driverSourceDiskRoot(entryPath);
    if (sourceRoot != std::string("")) {
        localRoots->push_back(std::make_shared<DriverSourceRoot>(std::string("/src"), sourceRoot));
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>> acquisitions = std::make_shared<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>(std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>{});
    std::shared_ptr<std::vector<std::shared_ptr<DriverAcquiredSource>>> acquiredSources = std::make_shared<std::vector<std::shared_ptr<DriverAcquiredSource>>>(std::vector<std::shared_ptr<DriverAcquiredSource>>{});
    if (stdlibRoot != std::string("")) {
        const auto acquisition = std::make_shared<::app_src_module_acquisition_::ModuleAcquisition>(std::string("/std"), [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(stdlibRoot); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 380, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
        acquisitions->push_back(acquisition);
        acquiredSources->push_back(std::make_shared<DriverAcquiredSource>(acquisition, driverLogicalPrefix(rootManifest->rootDirectory), std::string("local"), std::string(""), std::string(""), std::string(""), std::string(""), std::string(""), std::string(""), true));
    }
    auto _binding_value_16 = ::std_::fs::index::readTextResource(std::string("std-catalog.json"));
    if (doof::is_failure(_binding_value_16)) {
        const auto& catalogSource = _binding_value_16;
        return doof::Failure<std::string>{ std::string("Could not read embedded std-catalog.json") };
    }
    const auto catalogSource = doof::success_value(_binding_value_16);
    auto _try_value_17 = ::app_src_std_catalog_::parseStdCatalog(catalogSource);
    if (doof::is_failure(_try_value_17)) return doof::Failure<std::string>{doof::failure_error(_try_value_17)};
    const auto catalog = doof::success_value(_try_value_17);
    const auto packageAcquisitionRoot = ::app_src_package_acquisition_::workspacePackageAcquisitionRoot(rootManifest->rootDirectory);
    const auto platformName = ((nativePlatform == std::string("")) ? hostPlatform() : nativePlatform);
    auto _try_value_18 = configureDeclaredDependencies(rootManifest, std::string(""), rootManifest, packageAcquisitionRoot, platformName, acquisitions, acquiredSources);
    if (doof::is_failure(_try_value_18)) return doof::Failure<std::string>{doof::failure_error(_try_value_18)};
    (configuredDriverSourceState = std::make_shared<DriverSourceState>(localRoots, acquisitions, acquiredSources, std::make_shared<std::vector<std::shared_ptr<DriverReachedPackage>>>(std::vector<std::shared_ptr<DriverReachedPackage>>{}), namespaceMappings, ((nativePlatform == std::string("")) ? hostPlatform() : nativePlatform), (doof::is_null(externalTarget) ? std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(((nativePlatform == std::string("")) ? hostPlatform() : nativePlatform), std::string(""), std::string(""), std::string(""), 1) : doof::unwrap_optional(externalTarget)), rootManifest, catalog, packageAcquisitionRoot));
    return doof::Success<doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>>{ configuredDriverSource };
}
doof::Result<void, std::string> configureDeclaredDependencies(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::string& ownerPrefix, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest, const std::string& packageAcquisitionRoot, const std::string& nativePlatform, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>& acquisitions, const std::shared_ptr<std::vector<std::shared_ptr<DriverAcquiredSource>>>& acquiredSources) {
    const auto& _iterable_19 = manifest->dependencies;
    for (const auto& requested : *_iterable_19) {
        if (doof::string_startsWith(requested->name, std::string("std/"))) {
            continue;
        }
        const auto selected = ::app_src_dependency_policy_::selectedPackageSource(requested, rootManifest->packageResolutions);
        const auto logicalPrefix = (std::string("/") + requested->name);
        auto diskRoot = std::string("");
        auto sourceKind = std::string("local");
        auto sourceUrl = std::string("");
        auto sourceRef = std::string("");
        auto sourceCommit = std::string("");
        auto mutable_ = false;
        if (selected->path != std::string("")) {
            (diskRoot = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(selected->path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 431, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
            (mutable_ = true);
        } else {
            auto _binding_value_20 = ::app_src_package_acquisition_::acquireExactGitPackage(std::make_shared<::app_src_package_acquisition_::ExactPackageSource>(selected->name, std::string(""), selected->url, selected->ref, selected->commit), packageAcquisitionRoot);
            if (doof::is_failure(_binding_value_20)) {
                const auto error = doof::failure_error(_binding_value_20);
                return doof::Failure<std::string>{ error };
            }
            const auto acquired = doof::success_value(_binding_value_20);
            (diskRoot = acquired->rootDirectory);
            (sourceKind = std::string("git"));
            (sourceUrl = ::app_src_std_catalog_::canonicalDependencyUrl(selected->url));
            (sourceRef = selected->ref);
            (sourceCommit = selected->commit);
        }
        const auto& _iterable_21 = acquiredSources;
        for (const auto& existing : *_iterable_21) {
            if ((((sourceUrl != std::string("")) && (existing->sourceUrl != std::string(""))) && (::app_src_std_catalog_::canonicalDependencyUrl(existing->sourceUrl) == sourceUrl)) && (existing->sourceCommit != sourceCommit)) {
                return doof::Failure<std::string>{ ((std::string("Conflicting package revisions for ") + sourceUrl) + std::string("; add a root resolutions.packages entry")) };
            }
            if (existing->acquisition->logicalPrefix == logicalPrefix) {
                if (existing->acquisition->diskRoot != diskRoot) {
                    return doof::Failure<std::string>{ ((std::string("Package import prefix ") + logicalPrefix) + std::string(" resolves to multiple packages")) };
                }
                (diskRoot = std::string(""));
            }
        }
        if (diskRoot == std::string("")) {
            continue;
        }
        const auto acquisition = std::make_shared<::app_src_module_acquisition_::ModuleAcquisition>(logicalPrefix, diskRoot);
        acquisitions->push_back(acquisition);
        acquiredSources->push_back(std::make_shared<DriverAcquiredSource>(acquisition, ownerPrefix, sourceKind, sourceUrl, sourceRef, sourceCommit, ((requested->url == std::string("")) ? std::string("") : ::app_src_std_catalog_::canonicalDependencyUrl(requested->url)), requested->ref, requested->commit, mutable_));
        const auto dependencyManifestPath = ::app_src_module_acquisition_::acquiredManifestPath(acquisition);
        auto _binding_value_22 = ::doof_fs::readText(dependencyManifestPath);
        if (doof::is_failure(_binding_value_22)) {
            const auto& dependencySource = _binding_value_22;
            return doof::Failure<std::string>{ (std::string("Could not read dependency manifest ") + dependencyManifestPath) };
        }
        const auto dependencySource = doof::success_value(_binding_value_22);
        auto _try_value_23 = ::app_src_package_manifest_::parsePackageManifest(dependencySource, dependencyManifestPath, diskRoot, nativePlatform, std::string(""));
        if (doof::is_failure(_try_value_23)) return doof::Failure<std::string>{doof::failure_error(_try_value_23)};
        const auto dependencyManifest = doof::success_value(_try_value_23);
        if (dependencyManifest->name == std::string("")) {
            return doof::Failure<std::string>{ (std::string("Dependency package must declare a name: ") + dependencyManifestPath) };
        }
        if ((static_cast<int32_t>((dependencyManifest->packageResolutions)->size()) > 0) || (static_cast<int32_t>((dependencyManifest->externalResolutions)->size()) > 0)) {
            return doof::Failure<std::string>{ (std::string("resolutions are only allowed in the root doof.json: ") + dependencyManifestPath) };
        }
        auto _try_value_24 = configureDeclaredDependencies(dependencyManifest, logicalPrefix, rootManifest, packageAcquisitionRoot, nativePlatform, acquisitions, acquiredSources);
        if (doof::is_failure(_try_value_24)) return doof::Failure<std::string>{doof::failure_error(_try_value_24)};
    }
    return doof::Success<void>{};
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> reachedPackageInputs(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> result = std::make_shared<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>>(std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>{std::make_shared<::app_src_dependency_policy_::ReachedPackageInput>(driverLogicalPrefix(rootManifest->rootDirectory), std::string(""), rootManifest, std::string("root"), std::string(""), std::string(""), std::string(""), std::string(""), std::string(""), std::string(""), false)});
    const auto& _iterable_25 = configuredDriverSourceState->reachedPackages;
    for (const auto& reached : *_iterable_25) {
        result->push_back(std::make_shared<::app_src_dependency_policy_::ReachedPackageInput>(reached->acquisition->logicalPrefix, reached->introducedBy, reached->manifest, reached->sourceKind, reached->sourceUrl, reached->sourceRef, reached->sourceCommit, reached->requestedUrl, reached->requestedRef, reached->requestedCommit, reached->mutable_));
    }
    return result;
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>, std::string> resolvedDependencyInputs(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest) {
    const auto packages = reachedPackageInputs(rootManifest);
    auto _try_value_26 = ::app_src_dependency_policy_::resolveExternalInputs(packages, rootManifest);
    if (doof::is_failure(_try_value_26)) return doof::Failure<std::string>{doof::failure_error(_try_value_26)};
    const auto externals = doof::success_value(_try_value_26);
    auto _try_value_27 = ::app_src_dependency_policy_::validateDependencyPolicy(packages, externals, rootManifest);
    if (doof::is_failure(_try_value_27)) return doof::Failure<std::string>{doof::failure_error(_try_value_27)};
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>>{ externals };
}
doof::Result<void, std::string> acquireResolvedExternalInputs(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>& inputs, const std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>& target) {
    const auto& _iterable_28 = inputs;
    for (const auto& input : *_iterable_28) {
        const auto dependency = selectedExternalDependency(input);
        const auto manifest = std::make_shared<::app_src_package_manifest_::PackageManifest>(input->owner->manifest->name, std::string("1.0"), input->owner->manifest->manifestPath, input->owner->manifest->rootDirectory, std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>{dependency}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<::app_src_package_manifest_::DependencyPolicy>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::make_shared<::app_src_package_manifest_::NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::string(""), nullptr, nullptr, nullptr, nullptr);
        auto _try_value_29 = ::app_src_external_dependency_::acquirePackageExternalDependencies(manifest, target);
        if (doof::is_failure(_try_value_29)) return doof::Failure<std::string>{doof::failure_error(_try_value_29)};
    }
    return doof::Success<void>{};
}
std::shared_ptr<::app_src_package_manifest_::ExternalDependency> selectedExternalDependency(const std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>& input) {
    const auto requested = input->dependency;
    return std::make_shared<::app_src_package_manifest_::ExternalDependency>(requested->name, input->selectedKind, input->selectedUrl, requested->destination, input->selectedSha256, requested->stripComponents, requested->copyFiles, input->selectedRef, input->selectedCommit, requested->commands);
}
doof::Result<std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>, std::string> externalTargetForRequest(const std::string& target, const std::string& nativePlatform, const std::string& iosDestination, const std::string& iosMinimumVersion) {
    if (target == std::string("wasm")) {
        return doof::Success<std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>>{ std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(std::string("wasm"), std::string(""), std::string("wasm32-unknown-emscripten"), std::string("wasm32-unknown-emscripten"), 1) };
    }
    if (!doof::string_startsWith(nativePlatform, std::string("ios-"))) {
        return doof::Success<std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>>{ std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(nativePlatform, std::string(""), std::string(""), std::string(""), 1) };
    }
    const auto sdkName = ((iosDestination == std::string("device")) ? std::string("iphoneos") : std::string("iphonesimulator"));
    const auto sdkResult = runNativeCommand(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--sdk"), sdkName, std::string("--show-sdk-path")}), std::nullopt, false, 262144LL);
    if (sdkResult->exitCode != 0) {
        return doof::Failure<std::string>{ ((std::string("Could not resolve the ") + sdkName) + std::string(" SDK for external dependencies")) };
    }
    const auto sdkPath = doof::string_trim(::doof_blob::NativeBlobReader::constructor(sdkResult->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((sdkResult->output)->size()))));
    const auto hostArchitecture = ::std_::os::index::architecture();
    auto _try_value_30 = ::app_src_ios_app_::iosTargetTriple(iosMinimumVersion, iosDestination, hostArchitecture);
    if (doof::is_failure(_try_value_30)) return doof::Failure<std::string>{doof::failure_error(_try_value_30)};
    const auto targetTriple = doof::success_value(_try_value_30);
    const auto configureHost = ((iosDestination == std::string("device")) ? std::string("aarch64-apple-darwin") : (((hostArchitecture == std::string("x86_64")) || (hostArchitecture == std::string("x64"))) ? std::string("x86_64-apple-darwin") : std::string("aarch64-apple-darwin")));
    return doof::Success<std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>>{ std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(nativePlatform, sdkPath, targetTriple, configureHost, 1) };
}
std::string driverLogicalPrefix(const std::string& path) {
    const auto absolutePath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 578, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    if (doof::string_startsWith(absolutePath, std::string("/"))) {
        return driverSourceSuffix(absolutePath);
    }
    return (std::string("/") + absolutePath);
}
std::string driverRootLogicalPrefix(const std::string& packageName, const std::string& rootDirectory) {
    if (doof::string_startsWith(packageName, std::string("std/"))) {
        return (std::string("/") + packageName);
    }
    return driverLogicalPrefix(rootDirectory);
}
std::string driverRootLogicalPath(const std::string& path, const std::string& rootDirectory, const std::string& packageName) {
    if (!doof::string_startsWith(packageName, std::string("std/"))) {
        return driverLogicalPath(path);
    }
    const auto prefix = driverRootLogicalPrefix(packageName, rootDirectory);
    const auto absolutePath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 591, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    const auto absoluteRoot = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(rootDirectory); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 592, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    if (absolutePath == absoluteRoot) {
        return prefix;
    }
    const auto rootPrefix = (doof::string_endsWith(absoluteRoot, std::string("/")) ? absoluteRoot : (absoluteRoot + std::string("/")));
    if (doof::string_startsWith(absolutePath, rootPrefix)) {
        return ((prefix + std::string("/")) + doof::string_substring(absolutePath, static_cast<int32_t>(rootPrefix.size()), static_cast<int32_t>(absolutePath.size())));
    }
    return driverLogicalPath(absolutePath);
}
std::string driverPackageOutputRoot(const std::string& logicalPrefix) {
    auto start = 0;
    while ((start < static_cast<int32_t>(logicalPrefix.size())) && (logicalPrefix[start] == U'\u002F')) {
        (start = (start + 1));
    }
    return doof::string_substring(logicalPrefix, start, static_cast<int32_t>(logicalPrefix.size()));
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_project_::NativePackageInput>>> projectNativePackages(const std::string& projectRoot, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& projectManifest, const std::string& stdlibRoot) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_project_::NativePackageInput>>> packages = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_project_::NativePackageInput>>>(std::vector<std::shared_ptr<::app_src_emitter_project_::NativePackageInput>>{std::make_shared<::app_src_emitter_project_::NativePackageInput>(driverRootLogicalPrefix(projectManifest->name, projectRoot), std::string(""), projectManifest)});
    if ((projectManifest->target == std::string("wasm")) && (stdlibRoot != std::string(""))) {
        const auto jsonRoot = ::app_src_project_::joinPath(stdlibRoot, std::string("json"));
        const auto jsonManifestPath = ::app_src_project_::joinPath(jsonRoot, std::string("doof.json"));
        const auto jsonManifest = [&]() -> std::shared_ptr<::app_src_package_manifest_::PackageManifest> { auto _try_value = ::app_src_package_manifest_::parsePackageManifest([&]() -> std::string { auto _try_value = ::doof_fs::readText(jsonManifestPath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 616, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }(), jsonManifestPath, jsonRoot, std::string("wasm"), std::string("")); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 616, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
        packages->push_back(std::make_shared<::app_src_emitter_project_::NativePackageInput>(std::string("/std/json"), std::string("std/json"), jsonManifest));
    }
    const auto& _iterable_31 = configuredDriverSourceState->reachedPackages;
    for (const auto& reached : *_iterable_31) {
        packages->push_back(std::make_shared<::app_src_emitter_project_::NativePackageInput>(reached->acquisition->logicalPrefix, driverPackageOutputRoot(reached->acquisition->logicalPrefix), reached->manifest));
    }
    return packages;
}
void ensureOutputDirectory(const std::string& path) {
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
        return;
    }
    const auto parent = ::app_src_project_::parentPath(path);
    if (parent != path) {
        ensureOutputDirectory(parent);
    }
    [&]() -> void { auto _try_value = ::doof_fs::mkdir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 637, std::string("try! failed"));  }();
}
void materializeNativeCopy(const std::string& sourcePath, const std::string& outputPath) {
    if (::doof_fs::isDirectory(sourcePath)) {
        ensureOutputDirectory(outputPath);
        const auto& _iterable_32 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 643, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_32) {
            materializeNativeCopy(::app_src_project_::joinPath(sourcePath, entry->name), ::app_src_project_::joinPath(outputPath, entry->name));
        }
        return;
    }
    ensureOutputDirectory(::app_src_project_::parentPath(outputPath));
    writeBlobIfChanged(outputPath, [&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::doof_fs::readBlob(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 649, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }());
}
void writeTextIfChanged(const std::string& path, const std::string& content) {
    if (::doof_fs::exists(path)) {
        const auto existing = [&]() -> std::string { auto _try_value = ::doof_fs::readText(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 654, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        if (existing == content) {
            return;
        }
    }
    [&]() -> void { auto _try_value = ::doof_fs::writeText(path, content); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 657, std::string("try! failed"));  }();
}
std::string frontendCachePath(const std::string& buildDirectory, const std::string& kind) {
    return driverOutputPath(driverOutputPath(buildDirectory, std::string(".doof-cache/v1")), (kind + std::string(".json")));
}
std::string frontendConfigurationFingerprint(const std::string& entry, const std::string& entryMode, const std::string& target, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::string& stdlibRoot, const std::string& nativePlatform, const std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>& externalTarget) {
    const auto manifestSource = readTextOrEmpty(manifest->manifestPath);
    return ::std_::crypto::index::sha256HexString((((((((((((((((((((((std::string("doof-frontend-cache-2:") + doof::to_string(::app_src_frontend_cache_::FRONTEND_SEMANTIC_ABI)) + std::string("\n")) + entry) + std::string("\n")) + entryMode) + std::string("\n")) + target) + std::string("\n")) + stdlibRoot) + std::string("\n")) + nativePlatform) + std::string("\n")) + externalTarget->nativeTarget) + std::string("\n")) + externalTarget->sdkPath) + std::string("\n")) + externalTarget->targetTriple) + std::string("\n")) + configuredDriverSourceState->stdCatalog->digest) + std::string("\n")) + manifestSource));
}
std::string readTextOrEmpty(const std::string& path) {
    auto _binding_value_33 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_33)) {
        const auto& source = _binding_value_33;
        return std::string("");
    }
    const auto source = doof::success_value(_binding_value_33);
    return source;
}
std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState> readFrontendState(const std::string& path) {
    if (!::doof_fs::exists(path)) {
        return nullptr;
    }
    auto _binding_value_34 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_34)) {
        const auto& source = _binding_value_34;
        return nullptr;
    }
    const auto source = doof::success_value(_binding_value_34);
    return ::app_src_frontend_cache_::parseFrontendCacheState(source);
}
bool frontendStateMatches(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state, const std::string& configurationFingerprint, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader) {
    if (doof::is_null(state) || (state->configurationFingerprint != configurationFingerprint)) {
        return false;
    }
    const auto& _iterable_35 = state->fileInputs;
    for (const auto& input : *_iterable_35) {
        auto _binding_value_36 = ::doof_fs::readText(input->path);
        if (doof::is_failure(_binding_value_36)) {
            const auto& source = _binding_value_36;
            return false;
        }
        const auto source = doof::success_value(_binding_value_36);
        if (::std_::crypto::index::sha256HexString(source) != input->sourceHash) {
            return false;
        }
    }
    const auto& _iterable_37 = state->probes;
    for (const auto& probe : *_iterable_37) {
        auto _binding_value_38 = loader.call(probe->logicalPath);
        if (doof::is_failure(_binding_value_38)) {
            const auto& source = _binding_value_38;
            return false;
        }
        const auto source = doof::success_value(_binding_value_38);
        if (probe->missing) {
            if (!doof::is_null(source)) {
                return false;
            }
        } else {
            if (doof::is_null(source) || (::std_::crypto::index::sha256HexString(source->source) != probe->sourceHash)) {
                return false;
            }
        }
    }
    return true;
}
std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState> frontendStateForCompilation(const std::shared_ptr<::app_src_compiler_::Compilation>& result, const std::string& configurationFingerprint, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest) {
    const auto state = std::make_shared<::app_src_frontend_cache_::FrontendCacheState>(2, configurationFingerprint, std::make_shared<std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendSourceProbe>>>(std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendSourceProbe>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendFileInput>>>(std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendFileInput>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendModuleOutput>>>(std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendModuleOutput>>{}));
    const auto& _iterable_39 = result->resolutionProbes;
    for (const auto& path : *_iterable_39) {
        std::shared_ptr<::app_src_semantic_::SourceFile> matched = nullptr;
        const auto& _iterable_40 = result->sourceFiles;
        for (const auto& source : *_iterable_40) {
            if (source->path == path) {
                (matched = source);
            }
        }
        state->probes->push_back(std::make_shared<::app_src_frontend_cache_::FrontendSourceProbe>(path, (doof::is_null(matched) ? std::string("") : ::std_::crypto::index::sha256HexString(matched->source)), doof::is_null(matched)));
    }
    addFrontendFileInput(state->fileInputs, rootManifest->manifestPath);
    const auto& _iterable_41 = configuredDriverSourceState->reachedPackages;
    for (const auto& reached : *_iterable_41) {
        addFrontendFileInput(state->fileInputs, reached->manifest->manifestPath);
    }
    if (!doof::is_null(result->emission)) {
        const auto& _iterable_42 = result->emission->modules;
        for (const auto& module : *_iterable_42) {
            state->modules->push_back(std::make_shared<::app_src_frontend_cache_::FrontendModuleOutput>(module->modulePath, module->headerName, module->sourceName, module->fingerprint));
        }
    }
    return state;
}
std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> cachedModuleGraph(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state, const std::string& outputDirectory) {
    if (static_cast<int32_t>((state->modules)->size()) == 0) {
        return nullptr;
    }
    const auto graph = std::make_shared<::app_src_emitter_module_::ModuleGraphEmission>(std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>{}), std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    const auto& _iterable_43 = state->modules;
    for (const auto& module : *_iterable_43) {
        if (!::doof_fs::exists(driverOutputPath(outputDirectory, module->headerName)) || !::doof_fs::exists(driverOutputPath(outputDirectory, module->sourceName))) {
            return nullptr;
        }
        graph->modules->push_back(std::make_shared<::app_src_emitter_module_::ModuleEmission>(module->modulePath, std::string(""), std::string(""), module->headerName, module->sourceName, -1, std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}), true, module->fingerprint));
    }
    return graph;
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>> reusableEmissionKeys(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state, const std::string& outputDirectory) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>> keys = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>{});
    if (doof::is_null(state)) {
        return keys;
    }
    const auto& _iterable_44 = state->modules;
    for (const auto& module : *_iterable_44) {
        if (((module->fingerprint == std::string("")) || !::doof_fs::exists(driverOutputPath(outputDirectory, module->headerName))) || !::doof_fs::exists(driverOutputPath(outputDirectory, module->sourceName))) {
            continue;
        }
        keys->push_back(std::make_shared<::app_src_emitter_module_::ModuleEmissionCacheKey>(module->modulePath, module->fingerprint));
    }
    return keys;
}
void addFrontendFileInput(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendFileInput>>>& inputs, const std::string& path) {
    const auto& _iterable_45 = inputs;
    for (const auto& input : *_iterable_45) {
        if (input->path == path) {
            return;
        }
    }
    auto _binding_value_46 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_46)) {
        const auto& source = _binding_value_46;
        return;
    }
    const auto source = doof::success_value(_binding_value_46);
    inputs->push_back(std::make_shared<::app_src_frontend_cache_::FrontendFileInput>(path, ::std_::crypto::index::sha256HexString(source)));
}
void writeFrontendState(const std::string& path, const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state) {
    ensureOutputDirectory(::app_src_project_::parentPath(path));
    const auto temporaryPath = (path + std::string(".tmp"));
    [&]() -> void { auto _try_value = ::doof_fs::writeText(temporaryPath, ::app_src_frontend_cache_::renderFrontendCacheState(state)); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 781, std::string("try! failed"));  }();
    [&]() -> void { auto _try_value = ::doof_fs::rename(temporaryPath, path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 782, std::string("try! failed"));  }();
}
void removeStaleFrontendOutputs(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& previous, const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& current, const std::string& outputDirectory) {
    if (doof::is_null(previous)) {
        return;
    }
    const auto prefix = (doof::string_endsWith(outputDirectory, std::string("/")) ? outputDirectory : (outputDirectory + std::string("/")));
    const auto& _iterable_47 = previous->modules;
    for (const auto& old : *_iterable_47) {
        auto retained = false;
        const auto& _iterable_48 = current->modules;
        for (const auto& module : *_iterable_48) {
            if (((module->modulePath == old->modulePath) && (module->headerName == old->headerName)) && (module->sourceName == old->sourceName)) {
                (retained = true);
            }
        }
        if (retained) {
            continue;
        }
        const auto& _iterable_49 = std::make_shared<std::vector<std::string>>(std::vector<std::string>{old->headerName, old->sourceName});
        for (const auto& name : *_iterable_49) {
            const auto path = driverOutputPath(outputDirectory, name);
            if ((doof::string_startsWith(path, prefix) && ::doof_fs::exists(path)) && !::doof_fs::isDirectory(path)) {
                [&]() -> void { auto _try_value = ::doof_fs::remove(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 802, std::string("try! failed"));  }();
            }
        }
    }
}
void writeBlobIfChanged(const std::string& path, const std::shared_ptr<std::vector<uint8_t>>& content) {
    if (::doof_fs::exists(path)) {
        const auto existing = [&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::doof_fs::readBlob(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 809, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        if (blobsEqual(existing, content)) {
            return;
        }
    }
    [&]() -> void { auto _try_value = ::doof_fs::writeBlob(path, content); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 812, std::string("try! failed"));  }();
}
bool blobsEqual(const std::shared_ptr<std::vector<uint8_t>>& left, const std::shared_ptr<std::vector<uint8_t>>& right) {
    if (static_cast<int32_t>((left)->size()) != static_cast<int32_t>((right)->size())) {
        return false;
    }
    for (int32_t index = 0; index < static_cast<int32_t>((left)->size()); ++index) {
        if ((*left)[index] != (*right)[index]) {
            return false;
        }
    }
    return true;
}
void materializeProject(const std::string& outputDirectory, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project) {
    ensureOutputDirectory(outputDirectory);
    const auto& _iterable_50 = project->modules;
    for (const auto& module : *_iterable_50) {
        if (module->reused) {
            continue;
        }
        writeTextIfChanged(driverOutputPath(outputDirectory, module->headerName), module->header);
        writeTextIfChanged(driverOutputPath(outputDirectory, module->sourceName), module->source);
    }
    const auto& _iterable_51 = project->supportFiles;
    for (const auto& supportFile : *_iterable_51) {
        const auto outputPath = driverOutputPath(outputDirectory, supportFile->relativePath);
        ensureOutputDirectory(::app_src_project_::parentPath(outputPath));
        writeTextIfChanged(outputPath, supportFile->content);
    }
    const auto& _iterable_52 = project->nativeCopies;
    for (const auto& nativeCopy : *_iterable_52) {
        materializeNativeCopy(nativeCopy->sourcePath, driverOutputPath(outputDirectory, nativeCopy->relativePath));
    }
}
void materializeExecutableResources(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>& resources, const std::string& outputDirectory) {
    const auto& _iterable_53 = resources;
    for (const auto& resource : *_iterable_53) {
        const auto destinationRoot = driverOutputPath(outputDirectory, resource->destination);
        const auto outputPath = (::doof_fs::isDirectory(resource->sourcePath) ? destinationRoot : driverOutputPath(destinationRoot, ::app_src_project_::fileName(resource->sourcePath)));
        materializeNativeCopy(resource->sourcePath, outputPath);
    }
}
void materializeRuntimeHeader(const std::string& outputDirectory) {
    auto sourcePath = ::app_src_project_::environmentValue(std::string("DOOF_RUNTIME_HEADER"));
    const auto runtimeSource = ((sourcePath == std::string("")) ? ::std_::fs::index::readTextResource(std::string("doof_runtime.h")) : ::doof_fs::readText(sourcePath));
    writeTextIfChanged(driverOutputPath(outputDirectory, std::string("doof_runtime.hpp")), [&]() -> std::string { auto _try_value = runtimeSource; if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 858, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }());
}
std::string buildOutputName(const std::string& projectName) {
    return doof::string_replaceAll(doof::string_replaceAll(projectName, std::string("/"), std::string("-")), std::string("\\"), std::string("-"));
}
void printDiagnostics(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
    const auto displayCount = ((static_cast<int32_t>((diagnostics)->size()) < MAX_PRINTED_DIAGNOSTICS) ? static_cast<int32_t>((diagnostics)->size()) : MAX_PRINTED_DIAGNOSTICS);
    for (int32_t index = 0; index < displayCount; ++index) {
        const auto diagnostic = (*diagnostics)[index];
        doof::println(((((((((diagnostic->module + std::string(":")) + doof::to_string(diagnostic->span.start.line)) + std::string(":")) + doof::to_string(diagnostic->span.start.column)) + std::string(": ")) + diagnostic->severity) + std::string(": ")) + diagnostic->message));
    }
    if (static_cast<int32_t>((diagnostics)->size()) > displayCount) {
        doof::println(((std::string("... ") + doof::to_string((static_cast<int32_t>((diagnostics)->size()) - displayCount))) + std::string(" more diagnostics omitted")));
    }
}
void collectTestFiles(const std::string& path, const std::shared_ptr<std::vector<std::string>>& results, bool root) {
    if (!::doof_fs::isDirectory(path)) {
        if (doof::string_endsWith(path, std::string(".do"))) {
            results->push_back(path);
        }
        return;
    }
    if (!root && ::doof_fs::exists(::app_src_project_::joinPath(path, std::string("doof.json")))) {
        return;
    }
    const auto entries = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 885, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
    const auto& _iterable_54 = entries;
    for (const auto& entry : *_iterable_54) {
        const auto entryPath = ::app_src_project_::joinPath(path, entry->name);
        if (entry->kind == ::std_::fs::types::EntryKind::Directory) {
            collectTestFiles(entryPath, results, false);
        } else if ((entry->kind == ::std_::fs::types::EntryKind::File) && doof::string_endsWith(entry->name, std::string(".test.do"))) {
            results->push_back(entryPath);
        }
    }
}
std::shared_ptr<std::vector<std::string>> sortedTestFiles(const std::shared_ptr<std::vector<std::string>>& values) {
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    auto last = std::string("");
    for (int32_t count = 0; count < static_cast<int32_t>((values)->size()); ++count) {
        std::optional<std::string> candidate = std::nullopt;
        const auto& _iterable_55 = values;
        for (const auto& value : *_iterable_55) {
            if (((static_cast<int32_t>((result)->size()) == 0) || (value > last)) && (doof::is_null(candidate) || (value < candidate.value()))) {
                (candidate = value);
            }
        }
        if (!doof::is_null(candidate)) {
            result->push_back(candidate.value());
            (last = candidate.value());
        }
    }
    return result;
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>> sortedDiscoveredTests(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>>& values) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>> result = std::make_shared<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>>(std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>{});
    auto last = std::string("");
    for (int32_t count = 0; count < static_cast<int32_t>((values)->size()); ++count) {
        std::shared_ptr<::app_src_test_runner_::DiscoveredTest> candidate = nullptr;
        const auto& _iterable_56 = values;
        for (const auto& value : *_iterable_56) {
            if (((static_cast<int32_t>((result)->size()) == 0) || (value->id > last)) && (doof::is_null(candidate) || (value->id < candidate->id))) {
                (candidate = value);
            }
        }
        if (!doof::is_null(candidate)) {
            result->push_back(doof::unwrap_optional(candidate));
            (last = candidate->id);
        }
    }
    return result;
}
void mergeCoverageGroup(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& groupModules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& groupHits, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& allModules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& allHits) {
    for (int32_t groupIndex = 0; groupIndex < static_cast<int32_t>((groupModules)->size()); ++groupIndex) {
        const auto groupModule = (*groupModules)[groupIndex];
        const auto diskPath = driverSourceDiskPath(groupModule->modulePath, configuredDriverSourceState->localRoots, configuredDriverSourceState->acquisitions);
        auto targetIndex = -1;
        for (int32_t index = 0; index < static_cast<int32_t>((allModules)->size()); ++index) {
            if ((*allModules)[index]->modulePath == diskPath) {
                (targetIndex = index);
            }
        }
        if (targetIndex < 0) {
            std::shared_ptr<std::vector<int32_t>> lines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
            const auto& _iterable_57 = groupModule->instrumentedLines;
            for (const auto& line : *_iterable_57) {
                lines->push_back(line);
            }
            allModules->push_back(std::make_shared<::app_src_emitter_module_::CoverageModuleMetadata>(static_cast<int32_t>((allModules)->size()), diskPath, lines));
            allHits->push_back(std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}));
            (targetIndex = (static_cast<int32_t>((allModules)->size()) - 1));
        }
        if (groupIndex < static_cast<int32_t>((groupHits)->size())) {
            const auto& _iterable_58 = (*groupHits)[groupIndex];
            for (const auto& line : *_iterable_58) {
                auto found = false;
                const auto& _iterable_59 = (*allHits)[targetIndex];
                for (const auto& existing : *_iterable_59) {
                    if (existing == line) {
                        (found = true);
                    }
                }
                if (!found) {
                    (*allHits)[targetIndex]->push_back(line);
                }
            }
        }
    }
}
void printCoverageSummary(const std::shared_ptr<::app_src_test_runner_::CoverageReport>& report) {
    doof::println(std::string("Coverage summary:"));
    const auto& _iterable_60 = report->files;
    for (const auto& file : *_iterable_60) {
        const auto percent = ((doof::to_string((file->percentTenths / 10)) + std::string(".")) + doof::to_string((file->percentTenths % 10)));
        doof::println(((((((((std::string("  ") + file->path) + std::string(": ")) + doof::to_string(file->covered)) + std::string("/")) + doof::to_string(file->total)) + std::string(" lines (")) + percent) + std::string("%)")));
    }
    const auto overall = ((doof::to_string((report->totalPercentTenths / 10)) + std::string(".")) + doof::to_string((report->totalPercentTenths % 10)));
    doof::println(((((((std::string("Overall: ") + doof::to_string(report->totalCovered)) + std::string("/")) + doof::to_string(report->totalLines)) + std::string(" lines (")) + overall) + std::string("%)")));
}
std::string coverageHtmlPath(const std::string& jsonPath) {
    if (doof::string_endsWith(jsonPath, std::string(".json"))) {
        return (doof::string_substring(jsonPath, 0, (static_cast<int32_t>(jsonPath.size()) - 5)) + std::string(".html"));
    }
    return (jsonPath + std::string(".html"));
}
std::string writeCoverageHtml(const std::shared_ptr<::app_src_test_runner_::CoverageReport>& report, const std::string& jsonPath, const std::string& rootDirectory) {
    const auto indexPath = coverageHtmlPath(jsonPath);
    const auto filesDirectory = (doof::string_substring(indexPath, 0, (static_cast<int32_t>(indexPath.size()) - 5)) + std::string("_files"));
    const auto filesDirectoryName = ::app_src_project_::fileName(filesDirectory);
    const auto& _iterable_61 = report->files;
    for (const auto& file : *_iterable_61) {
        const auto relativePage = ::app_src_test_runner_::coverageFileRelativePath(file->path);
        const auto pagePath = ::app_src_project_::joinPath(filesDirectory, relativePage);
        ensureOutputDirectory(::app_src_project_::parentPath(pagePath));
        auto depth = 1;
        for (int32_t index = 0; index < static_cast<int32_t>(relativePage.size()); ++index) {
            if (relativePage[index] == U'\u002F') {
                (depth += 1);
            }
        }
        const auto indexHref = (doof::string_repeat(std::string("../"), depth) + ::app_src_project_::fileName(indexPath));
        const auto sourcePath = ::app_src_project_::joinPath(rootDirectory, file->path);
        auto source = std::string("");
        if (::doof_fs::exists(sourcePath)) {
            (source = [&]() -> std::string { auto _try_value = ::doof_fs::readText(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 988, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }());
        }
        [&]() -> void { auto _try_value = ::doof_fs::writeText(pagePath, ::app_src_test_runner_::renderCoverageFileHtml(file, source, indexHref)); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 989, std::string("try! failed"));  }();
    }
    [&]() -> void { auto _try_value = ::doof_fs::writeText(indexPath, ::app_src_test_runner_::renderCoverageHtml(report, filesDirectoryName)); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 991, std::string("try! failed"));  }();
    return indexPath;
}
int32_t testRequest(const std::shared_ptr<::app_src_cli_::CliRequest>& request) {
    const auto target = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->entry); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 997, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    if (!::doof_fs::exists(target)) {
        doof::println((std::string("error: File not found: ") + target));
        return 1;
    }
    const auto rootDirectory = (::doof_fs::isDirectory(target) ? target : ::app_src_project_::parentPath(target));
    std::shared_ptr<std::vector<std::string>> testFiles = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    collectTestFiles(target, testFiles, true);
    (testFiles = sortedTestFiles(testFiles));
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>> discovered = std::make_shared<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>>(std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>{});
    const auto& _iterable_62 = testFiles;
    for (const auto& testFile : *_iterable_62) {
        auto _binding_value_63 = ::doof_fs::readText(testFile);
        if (doof::is_failure(_binding_value_63)) {
            const auto& source = _binding_value_63;
            doof::println((std::string("error: Could not read test file: ") + testFile));
            return 1;
        }
        const auto source = doof::success_value(_binding_value_63);
        const auto parser = std::make_shared<::app_src_parser_::Parser>(source, std::make_shared<std::vector<::app_src_lexer_::Token>>(std::vector<::app_src_lexer_::Token>{}), 0, false, std::string(""), 0, 0, 0);
        const auto parsed = [&]() -> doof::Result<std::shared_ptr<::app_src_ast_::Program>, std::string> { try { return doof::Success<std::shared_ptr<::app_src_ast_::Program>>{doof::callback<std::shared_ptr<::app_src_ast_::Program>()>([parser]() -> std::shared_ptr<::app_src_ast_::Program> { return parser->parse(); }).call()}; } catch (const doof::Panic& _panic) { return doof::Failure<std::string>{_panic.message()}; } }();
        auto _binding_value_64 = parsed;
        if (doof::is_failure(_binding_value_64)) {
            const auto failure = doof::failure_error(_binding_value_64);
            if (parser->errorMessage == std::string("")) {
                doof::panic(failure);
            }
            doof::println(::app_src_test_runner_::formatParseFailure(testFile, source, parser->errorLine, parser->errorColumn, parser->errorMessage));
            return 1;
        }
        const auto program = doof::success_value(_binding_value_64);
        const auto discovery = ::app_src_test_runner_::discoverModuleTests(program, testFile, rootDirectory);
        const auto& _iterable_65 = discovery->errors;
        for (const auto& error : *_iterable_65) {
            doof::println(error);
        }
        if (static_cast<int32_t>((discovery->errors)->size()) > 0) {
            return 1;
        }
        const auto& _iterable_66 = discovery->tests;
        for (const auto& test : *_iterable_66) {
            discovered->push_back(test);
        }
    }
    (discovered = sortedDiscoveredTests(discovered));
    const auto selected = ::app_src_test_runner_::filterDiscoveredTests(discovered, request->filter);
    if (static_cast<int32_t>((selected)->size()) == 0) {
        const auto suffix = ((request->filter == std::string("")) ? std::string("") : ((std::string(" matching \"") + request->filter) + std::string("\"")));
        doof::println(((std::string("error: No tests found under ") + target) + suffix));
        return 1;
    }
    if (request->listOnly) {
        const auto& _iterable_67 = selected;
        for (const auto& test : *_iterable_67) {
            doof::println(test->id);
        }
        return 0;
    }
    auto passed = 0;
    auto failed = 0;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>> coverageModules = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>{});
    std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> coverageHits = std::make_shared<std::vector<std::shared_ptr<std::vector<int32_t>>>>(std::vector<std::shared_ptr<std::vector<int32_t>>>{});
    const auto groups = ::app_src_test_runner_::groupTestsForCompilation(selected);
    const auto& _iterable_68 = groups;
    for (const auto& group : *_iterable_68) {
        const auto moduleTests = group->tests;
        const auto testFile = (*moduleTests)[0]->modulePath;
        const auto project = ::app_src_project_::readProjectSpec(testFile, hostPlatform(), std::string(""));
        const auto buildRoot = ((request->outputDirectory == std::string("")) ? ::app_src_project_::joinPath(project->rootDirectory, project->buildDirectory) : [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->outputDirectory); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1047, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
        const auto coverageSuffix = (request->coverage ? std::string("-coverage") : std::string(""));
        const auto outputDirectory = ::app_src_project_::joinPath(::app_src_project_::joinPath(buildRoot, std::string(".doof-tests")), (group->outputName + coverageSuffix));
        const auto harnessPath = ::app_src_project_::joinPath(outputDirectory, std::string("__doof_tests__.do"));
        ensureOutputDirectory(outputDirectory);
        writeTextIfChanged(harnessPath, ::app_src_test_runner_::generateTestHarness(harnessPath, moduleTests));
        const auto stdlibRoot = ::app_src_project_::environmentValue(std::string("DOOF_STDLIB_ROOT"));
        const auto rootLogicalPrefix = driverRootLogicalPrefix(project->name, project->rootDirectory);
        std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>> namespaceMappings = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{std::make_shared<::app_src_emitter_names_::ModuleNamespaceMapping>(rootLogicalPrefix, project->name, std::string(""))});
        auto _binding_value_69 = sourceLoaderForRequest(harnessPath, stdlibRoot, namespaceMappings, project->manifest, std::string(""), nullptr);
        if (doof::is_failure(_binding_value_69)) {
            const auto error = doof::failure_error(_binding_value_69);
            doof::println((std::string("error: ") + error));
            return 1;
        }
        const auto loader = doof::success_value(_binding_value_69);
        const auto result = ::app_src_compiler_::compileWithLoader(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>(std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>{}), driverRootLogicalPath(harnessPath, project->rootDirectory, project->name), loader, namespaceMappings, std::string("executable"), request->coverage, std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>{}), std::string(""));
        if (static_cast<int32_t>((result->diagnostics)->size()) > 0) {
            printDiagnostics(result->diagnostics);
        }
        if (::app_src_diagnostics_::hasErrorDiagnostics(result->diagnostics)) {
            return 1;
        }
        if (doof::is_null(result->emission)) {
            doof::panic(std::string("test compiler produced no emission"));
        }
        const auto rootManifest = project->manifest;
        const auto testExternalTarget = std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(hostPlatform(), std::string(""), std::string(""), std::string(""), 1);
        auto _binding_value_70 = resolvedDependencyInputs(rootManifest);
        if (doof::is_failure(_binding_value_70)) {
            const auto error = doof::failure_error(_binding_value_70);
            doof::println((std::string("error: ") + error));
            return 1;
        }
        const auto externalInputs = doof::success_value(_binding_value_70);
        auto _binding_value_71 = acquireResolvedExternalInputs(externalInputs, testExternalTarget);
        if (doof::is_failure(_binding_value_71)) {
            const auto error = doof::failure_error(_binding_value_71);
            doof::println((std::string("error: ") + error));
            return 1;
        }
        const auto emission = ::app_src_emitter_project_::planProjectEmission(doof::unwrap_optional(result->emission), projectNativePackages(project->rootDirectory, rootManifest, std::string("")));
        if (request->coverage) {
            emission->nativeBuild->defines->push_back(std::string("DOOF_COVERAGE"));
        }
        materializeProject(outputDirectory, emission);
        materializeRuntimeHeader(outputDirectory);
        const auto binary = ::app_src_project_::joinPath(outputDirectory, std::string("doof-tests"));
        doof::println((std::string("BUILD ") + group->outputName));
        const auto buildExitCode = ::app_src_native_build_driver_::buildNativeProject(request->compiler, outputDirectory, binary, emission, false, hostPlatform());
        if (buildExitCode != 0) {
            return buildExitCode;
        }
        const auto& _iterable_72 = moduleTests;
        for (const auto& test : *_iterable_72) {
            const auto testResult = runNativeCommand(binary, std::make_shared<std::vector<std::string>>(std::vector<std::string>{test->id}), project->rootDirectory, !request->coverage, (request->coverage ? MAX_COVERAGE_OUTPUT_BYTES : MAX_NATIVE_COMPILER_OUTPUT_BYTES));
            if (request->coverage) {
                if (testResult->truncated) {
                    doof::println((((std::string("error: coverage output exceeded ") + doof::to_string(MAX_COVERAGE_OUTPUT_BYTES)) + std::string(" bytes for ")) + test->id));
                    return 1;
                }
                const auto output = ::doof_blob::NativeBlobReader::constructor(testResult->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((testResult->output)->size())));
                std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> groupHits = std::make_shared<std::vector<std::shared_ptr<std::vector<int32_t>>>>(std::vector<std::shared_ptr<std::vector<int32_t>>>{});
                const auto& _iterable_73 = result->emission->coverageModules;
                for (const auto& ignored : *_iterable_73) {
                    groupHits->push_back(std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}));
                }
                ::app_src_test_runner_::mergeCoverageOutput(output, result->emission->coverageModules, groupHits);
                mergeCoverageGroup(result->emission->coverageModules, groupHits, coverageModules, coverageHits);
                if (testResult->exitCode != 0) {
                    const auto visibleOutput = ::app_src_test_runner_::stripCoverageLines(output);
                    if (visibleOutput != std::string("")) {
                        doof::println(visibleOutput);
                    }
                }
            }
            const auto exitCode = testResult->exitCode;
            if (exitCode == 0) {
                (passed = (passed + 1));
                doof::println((std::string("PASS ") + test->id));
            } else {
                (failed = (failed + 1));
                doof::println((std::string("FAIL ") + test->id));
            }
        }
    }
    doof::println(((((std::string("Tests finished: ") + doof::to_string(passed)) + std::string(" passed, ")) + doof::to_string(failed)) + std::string(" failed")));
    if (request->coverage && (static_cast<int32_t>((coverageModules)->size()) > 0)) {
        const auto report = ::app_src_test_runner_::buildCoverageReport(coverageModules, coverageHits, rootDirectory);
        printCoverageSummary(report);
        const auto outputPath = ((request->coverageOutput == std::string("")) ? ::app_src_project_::joinPath(::app_src_project_::joinPath(rootDirectory, std::string("build")), std::string("coverage/doof-test-coverage.json")) : [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->coverageOutput); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1129, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
        ensureOutputDirectory(::app_src_project_::parentPath(outputPath));
        [&]() -> void { auto _try_value = ::doof_fs::writeText(outputPath, ::app_src_test_runner_::renderCoverageJson(report)); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1131, std::string("try! failed"));  }();
        doof::println((std::string("Coverage report written to ") + outputPath));
        const auto htmlPath = writeCoverageHtml(report, outputPath, rootDirectory);
        doof::println((std::string("Coverage HTML report written to ") + htmlPath));
    }
    return ((failed == 0) ? 0 : 1);
}
int32_t emitRequest(const std::shared_ptr<::app_src_cli_::CliRequest>& request) {
    auto project = ::app_src_project_::readProjectSpec(request->entry, hostPlatform(), request->targetOverride);
    const auto entryError = ::app_src_project_::projectEntryRequestError(project, request->entry);
    if (entryError != std::string("")) {
        doof::println((std::string("error: ") + entryError));
        return 1;
    }
    const auto iosDestination = ((request->command == std::string("package")) ? std::string("device") : request->iosDestination);
    const auto nativePlatform = (doof::is_null(project->iosApp) ? hostPlatform() : (std::string("ios-") + iosDestination));
    if (!doof::is_null(project->iosApp)) {
        (project = ::app_src_project_::readProjectSpec(request->entry, nativePlatform, request->targetOverride));
    }
    const auto iosMinimumVersion = (doof::is_null(project->iosApp) ? std::string("") : project->iosApp->minimumDeploymentTarget);
    auto _binding_value_74 = externalTargetForRequest(project->target, nativePlatform, iosDestination, iosMinimumVersion);
    if (doof::is_failure(_binding_value_74)) {
        const auto error = doof::failure_error(_binding_value_74);
        doof::println((std::string("error: ") + error));
        return 1;
    }
    const auto externalTarget = doof::success_value(_binding_value_74);
    const auto rootManifest = project->manifest;
    const auto entryPath = ::app_src_project_::joinPath(project->rootDirectory, project->entry);
    const auto entry = driverRootLogicalPath(entryPath, project->rootDirectory, project->name);
    const auto stdlibRoot = ::app_src_project_::environmentValue(std::string("DOOF_STDLIB_ROOT"));
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>> namespaceMappings = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{std::make_shared<::app_src_emitter_names_::ModuleNamespaceMapping>(driverRootLogicalPrefix(project->name, project->rootDirectory), project->name, std::string(""))});
    auto _binding_value_75 = sourceLoaderForRequest(entryPath, stdlibRoot, namespaceMappings, rootManifest, nativePlatform, externalTarget);
    if (doof::is_failure(_binding_value_75)) {
        const auto error = doof::failure_error(_binding_value_75);
        doof::println((std::string("error: ") + error));
        return 1;
    }
    const auto loader = doof::success_value(_binding_value_75);
    if (project->target == std::string("wasm")) {
        auto _binding_value_76 = ensureStdPackageReached(std::string("std/json"));
        if (doof::is_failure(_binding_value_76)) {
            const auto error = doof::failure_error(_binding_value_76);
            doof::println((std::string("error: ") + error));
            return 1;
        }
    }
    const auto entryMode = ((project->target == std::string("wasm")) ? std::string("wasm") : (doof::is_null(project->iosApp) ? std::string("executable") : std::string("ios-app")));
    const auto buildDirectory = ((request->outputDirectory == std::string("")) ? ::app_src_project_::joinPath(project->rootDirectory, project->buildDirectory) : [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->outputDirectory); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1178, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
    const auto outputDirectory = ((request->command == std::string("package")) ? ::app_src_project_::joinPath(buildDirectory, std::string("release")) : buildDirectory);
    const auto frontendConfiguration = frontendConfigurationFingerprint(entry, entryMode, project->target, rootManifest, stdlibRoot, nativePlatform, externalTarget);
    const auto checkCachePath = frontendCachePath(buildDirectory, std::string("check"));
    if ((request->command == std::string("check")) && frontendStateMatches(readFrontendState(checkCachePath), frontendConfiguration, loader)) {
        return 0;
    }
    const auto emissionCachePath = frontendCachePath(buildDirectory, std::string("emission"));
    const auto previousEmissionState = readFrontendState(emissionCachePath);
    auto reusedFrontend = false;
    auto result = std::make_shared<::app_src_compiler_::Compilation>(nullptr, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>(std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    const auto cachedGraph = ((((request->command == std::string("emit")) || (request->command == std::string("build"))) || (request->command == std::string("run"))) ? ((((project->target == std::string("wasm")) || (!doof::is_null(project->macosApp))) || (!doof::is_null(project->iosApp))) ? nullptr : ((frontendStateMatches(previousEmissionState, frontendConfiguration, loader) && (!doof::is_null(previousEmissionState))) ? cachedModuleGraph(doof::unwrap_optional(previousEmissionState), outputDirectory) : nullptr)) : nullptr);
    if (!doof::is_null(cachedGraph)) {
        (result = std::make_shared<::app_src_compiler_::Compilation>(doof::unwrap_optional(cachedGraph), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>(std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})));
        (reusedFrontend = true);
    } else {
        (result = ((request->command == std::string("check")) ? ::app_src_compiler_::checkWithLoader(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>(std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>{}), entry, loader, entryMode) : ::app_src_compiler_::compileWithLoader(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>(std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>{}), entry, loader, namespaceMappings, entryMode, false, ((request->command == std::string("package")) ? std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>{}) : reusableEmissionKeys(previousEmissionState, outputDirectory)), frontendConfiguration)));
    }
    if (static_cast<int32_t>((result->diagnostics)->size()) > 0) {
        printDiagnostics(result->diagnostics);
    }
    if (::app_src_diagnostics_::hasErrorDiagnostics(result->diagnostics)) {
        return 1;
    }
    if ((((request->command != std::string("check")) && (request->command != std::string("package"))) && !reusedFrontend) && (static_cast<int32_t>((result->diagnostics)->size()) == 0)) {
        writeFrontendState(checkCachePath, frontendStateForCompilation(result, frontendConfiguration, rootManifest));
    }
    if ((request->command == std::string("package")) && ::app_src_dependency_policy_::hasMutableStdPackageInputs(reachedPackageInputs(rootManifest))) {
        doof::println(std::string("warning: packaging with standard packages overridden by DOOF_STDLIB_ROOT; provenance.json will record them as mutable inputs"));
    }
    auto _binding_value_77 = resolvedDependencyInputs(rootManifest);
    if (doof::is_failure(_binding_value_77)) {
        const auto error = doof::failure_error(_binding_value_77);
        doof::println((std::string("error: ") + error));
        return 1;
    }
    const auto externalInputs = doof::success_value(_binding_value_77);
    if (request->command == std::string("check")) {
        if (static_cast<int32_t>((result->diagnostics)->size()) == 0) {
            writeFrontendState(checkCachePath, frontendStateForCompilation(result, frontendConfiguration, rootManifest));
        }
        return 0;
    }
    if (doof::is_null(result->emission)) {
        doof::panic(std::string("compiler produced no emission"));
    }
    auto _binding_value_78 = acquireResolvedExternalInputs(externalInputs, externalTarget);
    if (doof::is_failure(_binding_value_78)) {
        const auto error = doof::failure_error(_binding_value_78);
        doof::println((std::string("error: ") + error));
        return 1;
    }
    const auto emission = ::app_src_emitter_project_::planProjectEmission(doof::unwrap_optional(result->emission), projectNativePackages(project->rootDirectory, rootManifest, stdlibRoot));
    materializeProject(outputDirectory, emission);
    materializeRuntimeHeader(outputDirectory);
    writeTextIfChanged(driverOutputPath(outputDirectory, std::string("provenance.json")), ::app_src_provenance_::renderBuildProvenance(reachedPackageInputs(rootManifest), externalInputs, emission->nativeBuild, configuredDriverSourceState->stdCatalog));
    if ((((!reusedFrontend && (request->command != std::string("package"))) && (project->target != std::string("wasm"))) && doof::is_null(project->macosApp)) && doof::is_null(project->iosApp)) {
        const auto nextEmissionState = frontendStateForCompilation(result, frontendConfiguration, rootManifest);
        removeStaleFrontendOutputs(previousEmissionState, nextEmissionState, outputDirectory);
        writeFrontendState(emissionCachePath, nextEmissionState);
    }
    if (!doof::is_null(project->iosApp)) {
        auto _binding_value_79 = ::app_src_ios_app_driver_::configureIOSNativeBuild(outputDirectory, doof::unwrap_optional(project->iosApp), iosDestination, emission->nativeBuild);
        if (doof::is_failure(_binding_value_79)) {
            const auto error = doof::failure_error(_binding_value_79);
            doof::println((std::string("error: ") + error));
            return 1;
        }
    }
    if ((request->command == std::string("build")) || (request->command == std::string("run"))) {
        if ((request->command == std::string("run")) && (project->target == std::string("wasm"))) {
            doof::println(std::string("error: doof run is not supported for --target wasm; instantiate the generated .wasm from your host runtime"));
            return 1;
        }
        const auto executableName = ((project->target == std::string("wasm")) ? (buildOutputName(project->name) + std::string(".wasm")) : ((!doof::is_null(project->macosApp)) ? project->macosApp->executableName : ((!doof::is_null(project->iosApp)) ? project->iosApp->executableName : buildOutputName(project->name))));
        const auto outputPath = driverOutputPath(outputDirectory, executableName);
        if (doof::is_null(project->macosApp) && doof::is_null(project->iosApp)) {
            materializeExecutableResources(project->resources, outputDirectory);
        }
        const auto exitCode = ::app_src_native_build_driver_::buildNativeProject(request->compiler, outputDirectory, outputPath, emission, false, hostPlatform());
        if (exitCode != 0) {
            return exitCode;
        }
        if (!doof::is_null(project->iosApp)) {
            auto _binding_value_80 = ::app_src_ios_app_driver_::assembleIOSApp(outputDirectory, outputPath, doof::unwrap_optional(project->iosApp), iosDestination);
            if (doof::is_failure(_binding_value_80)) {
                const auto error = doof::failure_error(_binding_value_80);
                doof::println((std::string("error: ") + error));
                return 1;
            }
            const auto appPath = doof::success_value(_binding_value_80);
            if (request->command == std::string("build")) {
                return 0;
            }
            if (iosDestination == std::string("device")) {
                const auto signingWorkDirectory = driverOutputPath(outputDirectory, std::string(".doof-ios-signing-resolution"));
                auto _binding_value_81 = ::app_src_ios_device_::resolveIOSDeviceSigningOptions(project->iosApp->bundleId, request->iosSignIdentity, request->iosProvisioningProfile, signingWorkDirectory, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                if (doof::is_failure(_binding_value_81)) {
                    const auto error = doof::failure_error(_binding_value_81);
                    doof::println((std::string("error: ") + error));
                    return 1;
                }
                const auto signing = doof::success_value(_binding_value_81);
                auto _binding_value_82 = ::app_src_ios_device_::signIOSDeviceApp(appPath, project->iosApp->bundleId, signing, driverOutputPath(outputDirectory, std::string(".doof-ios-sign")));
                if (doof::is_failure(_binding_value_82)) {
                    const auto error = doof::failure_error(_binding_value_82);
                    doof::println((std::string("error: ") + error));
                    return 1;
                }
                auto _binding_value_83 = ::app_src_ios_device_::resolveIOSDeviceIdentifier(request->iosDevice, driverOutputPath(outputDirectory, std::string(".doof-ios-device-discovery")));
                if (doof::is_failure(_binding_value_83)) {
                    const auto error = doof::failure_error(_binding_value_83);
                    doof::println((std::string("error: ") + error));
                    return 1;
                }
                const auto deviceIdentifier = doof::success_value(_binding_value_83);
                const auto installPlan = ::app_src_run_command_::planIOSDeviceInstall(appPath, deviceIdentifier, project->rootDirectory);
                const auto installResult = runNativeCommand(installPlan->command, installPlan->arguments, installPlan->directory, true, 262144LL);
                if (installResult->error != std::string("")) {
                    doof::println((std::string("error: ") + installResult->error));
                }
                if (installResult->exitCode != 0) {
                    return installResult->exitCode;
                }
                const auto launchPlan = ::app_src_run_command_::planIOSDeviceLaunch(project->iosApp->bundleId, deviceIdentifier, project->rootDirectory);
                const auto launchResult = runNativeCommand(launchPlan->command, launchPlan->arguments, launchPlan->directory, true, 262144LL);
                if (launchResult->error != std::string("")) {
                    doof::println((std::string("error: ") + launchResult->error));
                }
                return launchResult->exitCode;
            }
            const auto installPlan = ::app_src_run_command_::planIOSSimulatorInstall(appPath, project->rootDirectory);
            const auto installResult = runNativeCommand(installPlan->command, installPlan->arguments, installPlan->directory, true, 262144LL);
            if (installResult->error != std::string("")) {
                doof::println((std::string("error: ") + installResult->error));
            }
            if (installResult->exitCode != 0) {
                return installResult->exitCode;
            }
            const auto launchPlan = ::app_src_run_command_::planIOSSimulatorLaunch(project->iosApp->bundleId, project->rootDirectory);
            const auto launchResult = runNativeCommand(launchPlan->command, launchPlan->arguments, launchPlan->directory, true, 262144LL);
            if (launchResult->error != std::string("")) {
                doof::println((std::string("error: ") + launchResult->error));
            }
            return launchResult->exitCode;
        }
        if (!doof::is_null(project->macosApp)) {
            auto _binding_value_84 = ::app_src_macos_app_driver_::assembleMacOSApp(outputDirectory, outputPath, doof::unwrap_optional(project->macosApp), emission->nativeBuild->libraryPaths);
            if (doof::is_failure(_binding_value_84)) {
                const auto error = doof::failure_error(_binding_value_84);
                doof::println((std::string("error: ") + error));
                return 1;
            }
            const auto appPath = doof::success_value(_binding_value_84);
            if (request->command == std::string("build")) {
                return 0;
            }
            const auto launchPlan = ::app_src_run_command_::planMacOSAppRun(appPath, project->rootDirectory);
            const auto launchResult = runNativeCommand(launchPlan->command, launchPlan->arguments, launchPlan->directory, true, 262144LL);
            if (launchResult->error != std::string("")) {
                doof::println((std::string("error: ") + launchResult->error));
            }
            return launchResult->exitCode;
        }
        if (request->command == std::string("build")) {
            return 0;
        }
        const auto runPlan = ::app_src_run_command_::planNativeProgramRun(outputPath, request->programArguments, project->rootDirectory);
        const auto runResult = runNativeCommand(runPlan->command, runPlan->arguments, runPlan->directory, true, 262144LL);
        if (runResult->error != std::string("")) {
            doof::println((std::string("error: ") + runResult->error));
        }
        return runResult->exitCode;
    }
    if (request->command == std::string("package")) {
        if (doof::is_null(project->packageConfig)) {
            doof::panic(std::string("project package settings were not resolved"));
        }
        const auto distDirectory = ((request->distDirectory != std::string("")) ? [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->distDirectory); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1339, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }() : project->packageConfig->distDirectory);
        ensureOutputDirectory(distDirectory);
        const auto executableName = ((project->target == std::string("wasm")) ? (buildOutputName(project->name) + std::string(".wasm")) : ((!doof::is_null(project->macosApp)) ? project->macosApp->executableName : ((!doof::is_null(project->iosApp)) ? project->iosApp->executableName : buildOutputName(project->name))));
        const auto outputPath = ((doof::is_null(project->macosApp) && doof::is_null(project->iosApp)) ? driverOutputPath(distDirectory, executableName) : driverOutputPath(outputDirectory, executableName));
        const auto exitCode = ::app_src_native_build_driver_::buildNativeProject(request->compiler, outputDirectory, outputPath, emission, true, hostPlatform());
        if (exitCode != 0) {
            return exitCode;
        }
        if (doof::is_null(project->macosApp) && doof::is_null(project->iosApp)) {
            materializeExecutableResources(project->resources, distDirectory);
            return 0;
        }
        if (!doof::is_null(project->iosApp)) {
            auto _binding_value_85 = ::app_src_ios_app_driver_::assembleIOSApp(outputDirectory, outputPath, doof::unwrap_optional(project->iosApp), iosDestination);
            if (doof::is_failure(_binding_value_85)) {
                const auto error = doof::failure_error(_binding_value_85);
                doof::println((std::string("error: ") + error));
                return 1;
            }
            const auto appPath = doof::success_value(_binding_value_85);
            if (doof::is_null(project->iosPackageConfig)) {
                doof::panic(std::string("iOS package settings were not resolved"));
            }
            const auto iosConfig = doof::unwrap_optional(project->iosPackageConfig);
            const auto environmentIdentity = ::app_src_project_::environmentValue(std::string("DOOF_IOS_SIGN_IDENTITY"));
            if (environmentIdentity != std::string("")) {
                (iosConfig->identity = environmentIdentity);
            }
            if (request->iosSignIdentity != std::string("")) {
                (iosConfig->identity = request->iosSignIdentity);
            }
            const auto environmentProfile = ::app_src_project_::environmentValue(std::string("DOOF_IOS_PROVISIONING_PROFILE"));
            if (environmentProfile != std::string("")) {
                (iosConfig->provisioningProfilePath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(environmentProfile); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1362, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
            }
            if (request->iosProvisioningProfile != std::string("")) {
                (iosConfig->provisioningProfilePath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->iosProvisioningProfile); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1363, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
            }
            const auto archivePath = driverOutputPath(distDirectory, ::app_src_ios_app_::iosPackageArchiveName(project->iosApp->executableName, project->iosApp->version));
            auto _binding_value_86 = ::app_src_ios_app_driver_::signAndArchiveIOSApp(appPath, archivePath, project->iosApp->bundleId, iosConfig, outputDirectory);
            if (doof::is_failure(_binding_value_86)) {
                const auto error = doof::failure_error(_binding_value_86);
                doof::println((std::string("error: ") + error));
                return 1;
            }
            doof::println((std::string("Package: ") + archivePath));
            return 0;
        }
        auto _binding_value_87 = ::app_src_macos_app_driver_::assembleMacOSApp(outputDirectory, outputPath, doof::unwrap_optional(project->macosApp), emission->nativeBuild->libraryPaths);
        if (doof::is_failure(_binding_value_87)) {
            const auto error = doof::failure_error(_binding_value_87);
            doof::println((std::string("error: ") + error));
            return 1;
        }
        const auto appPath = doof::success_value(_binding_value_87);
        const auto packageConfig = doof::unwrap_optional(project->packageConfig);
        if (request->macosSigning != std::string("")) {
            (packageConfig->signing = request->macosSigning);
        }
        const auto environmentIdentity = ::app_src_project_::environmentValue(std::string("DOOF_MACOS_SIGN_IDENTITY"));
        if (environmentIdentity != std::string("")) {
            (packageConfig->identity = environmentIdentity);
        }
        if (request->macosSignIdentity != std::string("")) {
            (packageConfig->identity = request->macosSignIdentity);
        }
        if (request->macosSandbox) {
            (packageConfig->sandbox = true);
        }
        if (request->macosEntitlements != std::string("")) {
            (packageConfig->entitlementsPath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->macosEntitlements); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1382, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
        }
        const auto archivePath = driverOutputPath(distDirectory, ::app_src_macos_app_::macOSPackageArchiveName(project->macosApp->executableName, project->macosApp->version));
        auto _binding_value_88 = ::app_src_macos_app_driver_::signAndArchiveMacOSApp(appPath, archivePath, packageConfig, outputDirectory);
        if (doof::is_failure(_binding_value_88)) {
            const auto error = doof::failure_error(_binding_value_88);
            doof::println((std::string("error: ") + error));
            return 1;
        }
        doof::println((std::string("Package: ") + archivePath));
        return 0;
    }
    return 0;
}
int32_t doof_main(const std::shared_ptr<std::vector<std::string>>& args) {
    const auto parsed = ::app_src_cli_::parseCli(args);
    if (parsed->help) {
        doof::println(::app_src_cli_::cliUsage());
        return 0;
    }
    if (parsed->error != std::string("")) {
        doof::println((std::string("error: ") + parsed->error));
        doof::println(::app_src_cli_::cliUsage());
        return 2;
    }
    if (parsed->request->command == std::string("test")) {
        return testRequest(doof::unwrap_optional(parsed->request));
    }
    return emitRequest(doof::unwrap_optional(parsed->request));
}

void __doof_initialize_module() {
        configuredDriverSourceState = std::make_shared<DriverSourceState>(std::make_shared<std::vector<std::shared_ptr<DriverSourceRoot>>>(std::vector<std::shared_ptr<DriverSourceRoot>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>(std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>{}), std::make_shared<std::vector<std::shared_ptr<DriverAcquiredSource>>>(std::vector<std::shared_ptr<DriverAcquiredSource>>{}), std::make_shared<std::vector<std::shared_ptr<DriverReachedPackage>>>(std::vector<std::shared_ptr<DriverReachedPackage>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{}), std::string(""), std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(std::string(""), std::string(""), std::string(""), std::string(""), 1), std::make_shared<::app_src_package_manifest_::PackageManifest>(std::string(""), std::string("1.0"), std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<::app_src_package_manifest_::DependencyPolicy>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::make_shared<::app_src_package_manifest_::NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::string(""), nullptr, nullptr, nullptr, nullptr), std::make_shared<::app_src_std_catalog_::StdCatalog>(1, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_std_catalog_::StdCatalogPackage>>>(std::vector<std::shared_ptr<::app_src_std_catalog_::StdCatalogPackage>>{})), std::string(""));
}
}

int main(int argc, char** argv) { try { auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ::app_src_analyzer_::__doof_initialize_module(); ::app_src_emitter_names_::__doof_initialize_module(); ::std_::time::duration::__doof_initialize_module(); ::std_::time::temporal::__doof_initialize_module(); ::app_src_external_dependency_::__doof_initialize_module(); ::app_src_package_acquisition_::__doof_initialize_module(); ::app_src_driver_::__doof_initialize_module(); std::vector<std::string> args; for (int i = 1; i < argc; ++i) args.emplace_back(argv[i]); return app_src_driver_::doof_main(std::make_shared<std::vector<std::string>>(std::move(args))); } catch (const doof::Panic& _panic) { std::cerr << "panic: " << _panic.what() << std::endl; std::abort(); } catch (const std::exception& error) { std::cerr << "error: " << error.what() << std::endl; return 1; } }
