#include "src_project_build_lock.hpp"

namespace app_src_project_build_lock_ {
using namespace ::std_::fs::index;
using namespace ::std_::path::index;
std::string projectBuildLockPath(const std::string& root, const std::string& buildDirectory) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{root, buildDirectory, std::string(".doof.lock")}));
}
doof::Result<void, std::string> ensureLockDirectory(const std::string& directory) {
    if (::doof_fs::isDirectory(directory)) {
        return doof::Success<void>{};
    }
    const auto parent = ::std_::path::index::dirname(directory);
    if (parent != directory) {
        auto _try_value_1 = ensureLockDirectory(parent);
        if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_1))};
    }
    auto _binding_value_2 = ::doof_fs::mkdir(directory);
    if (doof::is_failure(_binding_value_2)) {
        if (!::doof_fs::isDirectory(directory)) {
            return doof::Failure<std::string>{ (std::string("Could not create project build directory: ") + directory) };
        }
    }
    return doof::Success<void>{};
}
doof::Result<std::shared_ptr<::std_::fs::file::File>, std::string> acquireProjectBuildLock(const std::string& root, const std::string& buildDirectory) {
    const auto directory = ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{root, buildDirectory}));
    auto _try_value_3 = ensureLockDirectory(directory);
    if (doof::is_failure(_try_value_3)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_3))};
    const auto path = projectBuildLockPath(root, buildDirectory);
    auto _binding_value_4 = ::std_::fs::file::File::constructor(path, ::std_::fs::types::FileMode::ReadWrite, true, ::std_::fs::types::FileLock::Exclusive, false, ::std_::blob::types::Endian::LittleEndian);
    if (doof::is_failure(_binding_value_4)) {
        const auto error = doof::failure_error(_binding_value_4);
        if (error != ::std_::fs::types::IoError::WouldBlock) {
            return doof::Failure<std::string>{ (std::string("Could not acquire project build lock: ") + path) };
        }
        (static_cast<void>(::doof::print_flushed(((std::string("Waiting for project build lock: ") + path) + std::string("\n")))), std::monostate{});
        while (true) {
            auto _binding_value_5 = ::std_::fs::file::File::constructor(path, ::std_::fs::types::FileMode::ReadWrite, true, ::std_::fs::types::FileLock::Exclusive, true, ::std_::blob::types::Endian::LittleEndian);
            if (doof::is_failure(_binding_value_5)) {
                const auto waitError = doof::failure_error(_binding_value_5);
                if (waitError == ::std_::fs::types::IoError::Interrupted) {
                    continue;
                }
                return doof::Failure<std::string>{ (std::string("Could not acquire project build lock: ") + path) };
            }
            const auto waiting = doof::success_value(_binding_value_5);
            return doof::Success<std::shared_ptr<::std_::fs::file::File>>{ waiting };
        }
    }
    const auto handle = doof::success_value(_binding_value_4);
    return doof::Success<std::shared_ptr<::std_::fs::file::File>>{ handle };
}
}
