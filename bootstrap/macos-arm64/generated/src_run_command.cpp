#include "src_run_command.hpp"
#include <cmath>
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_run_command_ {

doof::JsonObject RunInvocation::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["command"] = doof::json_value(this->command);
    (*_json)["arguments"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->arguments->size()); for (const auto& _element : *this->arguments) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["directory"] = doof::json_value(this->directory);
    return _json;
}
doof::Result<std::shared_ptr<RunInvocation>, std::string> RunInvocation::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_command = _object->find("command");
    if (_iterator_command == _object->end()) { return doof::Failure<std::string>{"Missing required field \"command\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_command->second) : doof::json_is_string(_iterator_command->second)))) { return doof::Failure<std::string>{"Field \"command\" expected string but got " + std::string(doof::json_type_name(_iterator_command->second))}; }
    auto _field_command = (_lenient ? doof::json_as_string_lenient(_iterator_command->second) : doof::json_as_string(_iterator_command->second));
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_arguments;
    if (auto _iterator_arguments = _object->find("arguments"); _iterator_arguments != _object->end()) {
        if (!(doof::json_is_array(_iterator_arguments->second))) { return doof::Failure<std::string>{"Field \"arguments\" expected array but got " + std::string(doof::json_type_name(_iterator_arguments->second))}; }
        _field_arguments = [&]() { const auto* _array = doof::json_as_array(_iterator_arguments->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_arguments = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    auto _iterator_directory = _object->find("directory");
    if (_iterator_directory == _object->end()) { return doof::Failure<std::string>{"Missing required field \"directory\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_directory->second) : doof::json_is_string(_iterator_directory->second)))) { return doof::Failure<std::string>{"Field \"directory\" expected string but got " + std::string(doof::json_type_name(_iterator_directory->second))}; }
    auto _field_directory = (_lenient ? doof::json_as_string_lenient(_iterator_directory->second) : doof::json_as_string(_iterator_directory->second));
    return doof::Success<std::shared_ptr<RunInvocation>>{std::make_shared<RunInvocation>(_field_command, _field_arguments.value(), _field_directory)};
}
std::shared_ptr<RunInvocation> planNativeProgramRun(std::string executablePath, std::shared_ptr<std::vector<std::string>> programArguments, std::string packageRoot) {
    return std::make_shared<RunInvocation>(executablePath, programArguments, packageRoot);
}
std::shared_ptr<RunInvocation> planMacOSAppRun(std::string appPath, std::string packageRoot) {
    return std::make_shared<RunInvocation>(std::string("open"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-n"), appPath}), packageRoot);
}
std::shared_ptr<RunInvocation> planIOSSimulatorInstall(std::string appPath, std::string packageRoot) {
    return std::make_shared<RunInvocation>(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("simctl"), std::string("install"), std::string("booted"), appPath}), packageRoot);
}
std::shared_ptr<RunInvocation> planIOSSimulatorLaunch(std::string bundleId, std::string packageRoot) {
    return std::make_shared<RunInvocation>(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("simctl"), std::string("launch"), std::string("booted"), bundleId}), packageRoot);
}
std::shared_ptr<RunInvocation> planIOSDeviceInstall(std::string appPath, std::string deviceIdentifier, std::string packageRoot) {
    return std::make_shared<RunInvocation>(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("devicectl"), std::string("device"), std::string("install"), std::string("app"), std::string("--device"), deviceIdentifier, appPath}), packageRoot);
}
std::shared_ptr<RunInvocation> planIOSDeviceLaunch(std::string bundleId, std::string deviceIdentifier, std::string packageRoot) {
    return std::make_shared<RunInvocation>(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("devicectl"), std::string("device"), std::string("process"), std::string("launch"), std::string("--device"), deviceIdentifier, std::string("--terminate-existing"), bundleId}), packageRoot);
}
}
