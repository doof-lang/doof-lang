#include "src_resolver.hpp"
#include <cmath>
#include "src_semantic.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_resolver_ {
using namespace ::app_src_semantic_;
doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> noSourceLoader(std::string path) {
    return doof::Success<std::shared_ptr<::app_src_semantic_::SourceFile>>{ nullptr };
}

std::shared_ptr<::app_src_semantic_::SourceFile> ModuleResolver::find(std::string path) {
    const auto& _iterable_1 = this->sources;
    for (const auto& source : *_iterable_1) {
        if (source->path == path) {
            return source;
        }
    }
    const auto& _iterable_2 = this->loadedPaths;
    for (const auto& loaded : *_iterable_2) {
        if (loaded == path) {
            return nullptr;
        }
    }
    this->loadedPaths->push_back(path);
    auto _binding_value_3 = this->loader.call(path);
    if (doof::is_failure(_binding_value_3)) {
        const auto diagnostic = doof::failure_error(_binding_value_3);
        this->failedPaths->push_back(path);
        this->diagnostics->push_back(diagnostic);
        return nullptr;
    }
    const auto loaded = doof::success_value(_binding_value_3);
    if (!doof::is_null(loaded)) {
        this->sources->push_back(doof::unwrap_optional(loaded));
        return doof::unwrap_optional(loaded);
    }
    return nullptr;
}
bool ModuleResolver::failed(std::string path) {
    const auto& _iterable_4 = this->failedPaths;
    for (const auto& failed : *_iterable_4) {
        if (failed == path) {
            return true;
        }
    }
    return false;
}
std::string ModuleResolver::resolve(std::string importer, std::string specifier) {
    const auto base = (doof::string_startsWith(specifier, std::string(".")) ? relativeBase(importer, specifier) : (std::string("/") + specifier));
    const auto exact = withExtension(base);
    if (doof::string_endsWith(base, std::string(".do"))) {
        return exact;
    }
    if (!doof::is_null(find(exact))) {
        return exact;
    }
    const auto barrel = (base + std::string("/index.do"));
    if (!doof::is_null(find(barrel))) {
        return barrel;
    }
    return exact;
}
std::string withExtension(std::string path) {
    if (doof::string_endsWith(path, std::string(".do"))) {
        return path;
    }
    return (path + std::string(".do"));
}
std::string relativeBase(std::string importer, std::string specifier) {
    auto directory = parentDirectory(importer);
    auto remaining = specifier;
    while (doof::string_startsWith(remaining, std::string("../"))) {
        (directory = parentDirectory(directory));
        (remaining = doof::string_substring(remaining, 3, static_cast<int32_t>(remaining.size())));
    }
    while (doof::string_startsWith(remaining, std::string("./"))) {
        (remaining = doof::string_substring(remaining, 2, static_cast<int32_t>(remaining.size())));
    }
    if (directory == std::string("/")) {
        return (std::string("/") + remaining);
    }
    return ((directory + std::string("/")) + remaining);
}
std::string parentDirectory(std::string path) {
    auto end = (static_cast<int32_t>(path.size()) - 1);
    while ((end >= 0) && (path[end] == U'\u002F')) {
        (end = (end - 1));
    }
    while ((end >= 0) && (path[end] != U'\u002F')) {
        (end = (end - 1));
    }
    if (end <= 0) {
        return std::string("/");
    }
    return doof::string_substring(path, 0, end);
}
}
