#include "src_stdlib_preparation.hpp"

namespace app_src_stdlib_preparation_ {
using namespace ::app_src_package_manifest_;
using namespace ::std_::blob::index;
using namespace ::std_::os::index;
using namespace ::std_::path::index;
int64_t MAX_STDLIB_PREPARATION_OUTPUT_BYTES = 1048576LL;

std::string applyStdlibPreparationSubstitutions(const std::string& value, const std::string& packageRoot, const std::shared_ptr<StdlibPreparationTarget>& target) {
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("${packageRoot}"), packageRoot), std::string("${jobs}"), doof::to_string(((target->jobs < 1) ? 1 : target->jobs))), std::string("${nativeTarget}"), target->nativeTarget), std::string("${sdkPath}"), target->sdkPath), std::string("${targetTriple}"), target->targetTriple), std::string("${configureHost}"), target->configureHost);
}
bool withinPackage(const std::string& path, const std::string& packageRoot) {
    const auto boundary = (doof::string_endsWith(packageRoot, std::string("/")) ? packageRoot : (packageRoot + std::string("/")));
    return ((path == packageRoot) || doof::string_startsWith(path, boundary));
}
doof::Result<void, std::string> runPreparationCommand(const std::shared_ptr<::app_src_package_manifest_::StdlibPreparationCommand>& command, int32_t index, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::shared_ptr<StdlibPreparationTarget>& target) {
    const auto workingDirectory = ((command->workingDirectory == std::string("")) ? manifest->rootDirectory : ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{manifest->rootDirectory, applyStdlibPreparationSubstitutions(command->workingDirectory, manifest->rootDirectory, target)})));
    if (!withinPackage(workingDirectory, manifest->rootDirectory)) {
        return doof::Failure<std::string>{ (std::string("Standard package preparation workingDirectory must stay within ") + manifest->rootDirectory) };
    }
    std::shared_ptr<doof::ordered_map<std::string, std::string>> environment = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
    const auto& _iterable_2 = command->env;
    for (const auto& [key, value] : *_iterable_2) {
        doof::map_set(environment, key, applyStdlibPreparationSubstitutions(value, manifest->rootDirectory, target), "", 0);
    }
    std::shared_ptr<std::vector<std::string>> arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_4 = command->args;
    for (const auto& argument : *_iterable_4) {
        arguments->push_back(applyStdlibPreparationSubstitutions(argument, manifest->rootDirectory, target));
    }
    const auto program = applyStdlibPreparationSubstitutions(command->program, manifest->rootDirectory, target);
    auto _binding_value_5 = ::std_::os::index::run(program, arguments, std::make_shared<::std_::os::index::ExecOptions>(workingDirectory, doof::map_drainToReadonly(environment, "", 0), true, false, true, false, ::std_::os::index::ProcessGroupMode::Isolated, MAX_STDLIB_PREPARATION_OUTPUT_BYTES, nullptr));
    if (doof::is_failure(_binding_value_5)) {
        const auto error = doof::failure_error(_binding_value_5);
        return doof::Failure<std::string>{ ((program + std::string(": ")) + error) };
    }
    const auto result = doof::success_value(_binding_value_5);
    const auto output = doof::string_trim(::doof_blob::NativeBlobReader::constructor(result->stdout_, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->stdout_)->size()))));
    if (result->exitCode != 0) {
        return doof::Failure<std::string>{ ((((((std::string("Standard package ") + manifest->name) + std::string(" preparation command ")) + doof::to_string((index + 1))) + std::string(" exited with code ")) + doof::to_string(result->exitCode)) + ((output == std::string("")) ? std::string("") : (std::string(":\n") + output))) };
    }
    return doof::Success<void>{};
}
doof::Result<void, std::string> prepareStdlibPackage(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::shared_ptr<StdlibPreparationTarget>& target) {
    for (int32_t index = 0; index < static_cast<int32_t>((manifest->stdlibPreparation)->size()); ++index) {
        auto _try_value_6 = runPreparationCommand(doof::array_at(manifest->stdlibPreparation, index, "src/stdlib-preparation", 76), index, manifest, target);
        if (doof::is_failure(_try_value_6)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_6))};
    }
    return doof::Success<void>{};
}
}
